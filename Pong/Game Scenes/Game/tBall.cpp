//
// tBall.cpp
//

#include "tBall.h"

#include <math.h>
#include <stdlib.h>

static const float kInitialPositionX = 450.0f;
static const float kInitialPositionY = 300.0f;

static const float kRadius = 8.0f;

//
// constructor
//
tBall::tBall()
{
}


//
// destructor
//
tBall::~tBall()
{
}


//
// getCurrentDirection()
//
CGPoint tBall::getCurrentDirection()
{
	return _currentDirection;
}


//
// setCurrentDirection()
//
void tBall::setCurrentDirection( const CGPoint& direction )
{
	_currentDirection = direction;
}


//
// getCurrentPosition()
//
CGPoint tBall::getCurrentPosition()
{
	return _currentPosition;
}


//
// setCurrentPosition()
//
void tBall::setCurrentPosition( const CGPoint& position )
{
	_currentPosition = position;
}


//
// setCurrentPositionX()
//
void tBall::setCurrentPositionX( float x )
{
	_currentPosition.x = x;
}


//
// setCurrentPositionY()
//
void tBall::setCurrentPositionY( float y )
{
	_currentPosition.y = y;
}


//
// getRadius()
//
float tBall::getRadius()
{
	return kRadius;
}


//
// start()
//
void tBall::start()
{
	reset();
}


//
// stop()
//
void tBall::stop()
{
}


//
// reset()
//
void tBall::reset()
{
	_currentPosition.x = kInitialPositionX;
	_currentPosition.y = kInitialPositionY;

	// Calculate a random direction vector for the ball.
	_currentDirection.x = ( ( float )rand() / ( float )RAND_MAX ) - 0.5f;
	_currentDirection.y = ( ( float )rand() / ( float )RAND_MAX ) - 0.5f;

	// Normalize the random direction vector to maintain a constant initial speed.
	float normalizingValue = ( float )sqrt( pow( _currentDirection.x, 2 ) + pow( _currentDirection.y, 2 ) );
	_currentDirection.x = _currentDirection.x / normalizingValue;
	_currentDirection.y = _currentDirection.y / normalizingValue;
}


//
// intersects
//
bool tBall::intersects( const CGRect& rectangle )
{
	CGPoint circleDistance = CGPointMake( abs( _currentPosition.x - ( rectangle.x + rectangle.width / 2.0f ) ),
		                                  abs( _currentPosition.y - ( rectangle.y - rectangle.height / 2.0f) ) );

	if( circleDistance.x > ( rectangle.width / 2.0f + kRadius ) ) { return false; }
    if( circleDistance.y > ( rectangle.height / 2.0f + kRadius ) ) { return false; }

    if( circleDistance.x <= ( rectangle.width / 2.0f ) ) { return true; }
    if( circleDistance.y <= ( rectangle.height / 2.0f ) ) { return true; }

    float cornerDistance_sq = pow( ( _currentPosition.x - ( rectangle.width / 2.0f ) ), 2 ) +
		                      pow( ( _currentPosition.y - ( rectangle.height / 2.0f ) ), 2 );

	return( cornerDistance_sq <= ( pow( kRadius, 2 ) ) );
}


//
// updatePosition()
//
void tBall::updatePosition( int deltaInMilliseconds )
{
	float timeFactor = deltaInMilliseconds / 4.0f;

	_currentPosition.x = _currentPosition.x + timeFactor * _currentDirection.x;
	_currentPosition.y = _currentPosition.y + timeFactor * _currentDirection.y;
}


//
// flipDirectionX()
//
void tBall::flipDirectionX()
{
	_currentDirection.x = -_currentDirection.x;
}


//
// flipDirectionY()
//
void tBall::flipDirectionY()
{
	_currentDirection.y = -_currentDirection.y;
}