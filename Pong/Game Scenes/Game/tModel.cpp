//
// tModel.cpp
//

#include "tModel.h"
#include "tBall.h"
#include "tPaddle.h"
#include "tWall.h"

static const int kMaxScore = 5;

static const float kTopWallPositionX = 50.0f;
static const float kTopWallPositionY = 600.0f;

static const float kBottomWallPositionX = 50.0f;
static const float kBottomWallPositionY = 15.0f; // This value should be equal to kWidth defined in tWall.cpp.

static const float kLeftPaddleInitialPositionX = 50.0f;
static const float kLeftPaddleInitialPositionY = 500.0f;

static const float kRightPaddleInitialPositionX = 835.0f;
static const float kRightPaddleInitialPositionY = 500.0f;

//
// constructor
//
tModel::tModel()
{
	_topWallPtr = new tWall( CGPointMake( kTopWallPositionX, kTopWallPositionY ) );
	_bottomWallPtr = new tWall( CGPointMake( kBottomWallPositionX, kBottomWallPositionY ) );
	_wallWidth = _topWallPtr->getWidth();

	_leftPaddlePtr = new tPaddle( CGPointMake( kLeftPaddleInitialPositionX, kLeftPaddleInitialPositionY ) );
	_rightPaddlePtr = new tPaddle( CGPointMake( kRightPaddleInitialPositionX, kRightPaddleInitialPositionY ) );
	_paddleWidth = _leftPaddlePtr->getWidth();
	_paddleHeight = _leftPaddlePtr->getHeight();

	_ballPtr = new tBall();
	_ballRadius = _ballPtr->getRadius();

	_leftPlayerScore = 0;
	_rightPlayerScore = 0;

	_isRunning = false;
}


//
// destructor
//
tModel::~tModel()
{
	delete _ballPtr;
	_ballPtr = NULL;

	delete _rightPaddlePtr;
	_rightPaddlePtr = NULL;

	delete _leftPaddlePtr;
	_leftPaddlePtr = NULL;

	delete _bottomWallPtr;
	_bottomWallPtr = NULL;

	delete _topWallPtr;
	_topWallPtr = NULL;
}


//
// start()
//
void tModel::start()
{
	_isRunning = true;

	_leftPlayerScore = 0;
	_rightPlayerScore = 0;

	_ballPtr->start();
}


//
// stop()
//
void tModel::stop()
{
	_isRunning = false;

	_ballPtr->stop();
}


//
// update()
//
void tModel::update( int deltaInMilliseconds )
{
	if( ( _leftPlayerScore < kMaxScore ) && ( _rightPlayerScore < kMaxScore ) && ( _isRunning == true ) )
	{
		_leftPaddlePtr->updatePosition( deltaInMilliseconds );
		_rightPaddlePtr->updatePosition( deltaInMilliseconds );
		_ballPtr->updatePosition( deltaInMilliseconds );

		// First, detect if the ball collides with the right paddle.
		// Then, detect if the ball collides with the left paddle.

		if( ( _ballPtr->intersects( CGRectMake( _rightPaddlePtr->getCurrentPosition().x, _rightPaddlePtr->getCurrentPosition().y, _paddleWidth, _paddleHeight ) ) == true ) &&
			( _ballPtr->getCurrentDirection().x > 0.0f ) )
		{
			_ballPtr->setCurrentPositionX( _rightPaddlePtr->getCurrentPosition().x - _ballRadius );

			// Change the sign of the x-component of the velocity vector and increase the velocity of the ball each time it collides with a paddle.
			_ballPtr->setCurrentDirection( CGPointMake( -_ballPtr->getCurrentDirection().x * 1.2f, _ballPtr->getCurrentDirection().y * 1.2f ) );
		}
		else if( ( _ballPtr->intersects( CGRectMake( _leftPaddlePtr->getCurrentPosition().x, _leftPaddlePtr->getCurrentPosition().y, _paddleWidth, _paddleHeight ) ) == true ) &&
			     ( _ballPtr->getCurrentDirection().x < 0.0f ) )
		{
			_ballPtr->setCurrentPositionX( _leftPaddlePtr->getCurrentPosition().x + _paddleWidth + _ballRadius );

			// Change the sign of the x-component of the velocity vector and increase the velocity of the ball each time it collides with a paddle.
			_ballPtr->setCurrentDirection( CGPointMake( -_ballPtr->getCurrentDirection().x * 1.2f, _ballPtr->getCurrentDirection().y * 1.2f ) );
		}

		// Then, detect if the ball collides with the top wall.
		// Then, detect if the ball collides with the bottom wall.
		if( ( _ballPtr->getCurrentPosition().y + _ballRadius ) >= ( 600 - _wallWidth ) )
		{
			_ballPtr->setCurrentPositionY( 600.0f - _wallWidth - _ballRadius );
			_ballPtr->flipDirectionY();
		}
		else if( ( _ballPtr->getCurrentPosition().y - _ballRadius ) <= _wallWidth )
		{
			_ballPtr->setCurrentPositionY( _wallWidth + _ballRadius );
			_ballPtr->flipDirectionY();
		}

		// Detect if the ball leaves the playing field.
		// Case 1: Ball leaves field to the right and left player scores point.
		// Case 2: Ball leaves field to the left and right player scores point.
		if( ( _ballPtr->getCurrentPosition().x - _ballRadius ) >= 900 )
		{
			_ballPtr->reset();
			_leftPlayerScore = _leftPlayerScore + 1;
		}
		else if( ( _ballPtr->getCurrentPosition().x + _ballRadius ) <= 0.0 )
		{
			_ballPtr->reset();
			_rightPlayerScore = _rightPlayerScore + 1;
		}
		else
		{
			// Do nothing since the ball is still in the playing field.
		}
	}
	else
	{
		// Do nothing since the game is over.
	}
}


//
// getPaddlePosition()
//
CGPoint tModel::getPaddlePosition( const tPaddle::tPaddleType& paddleType )
{
	CGPoint currentPosition;

	switch( paddleType )
	{
		case tPaddle::tPaddleType::kLeft:
		{
			currentPosition = _leftPaddlePtr->getCurrentPosition();
			break;
		}
		case tPaddle::tPaddleType::kRight:
		{
			currentPosition = _rightPaddlePtr->getCurrentPosition();
			break;
		}
		default:
		{
			// Do nothing.
		}
	}

	return currentPosition;
}


//
// movePaddle()
//
void tModel::movePaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction )
{
	switch( paddleType )
	{
		case tPaddle::tPaddleType::kLeft:
		{
			_leftPaddlePtr->move( direction );
			break;
		}
		case tPaddle::tPaddleType::kRight:
		{
			_rightPaddlePtr->move( direction );
			break;
		}
		default:
		{
			// Do nothing;
		}
	}
}


//
// stopPaddle()
//
void tModel::stopPaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction )
{
	switch( paddleType )
	{
		case tPaddle::tPaddleType::kLeft:
		{
			_leftPaddlePtr->stop( direction );
			break;
		}
		case tPaddle::tPaddleType::kRight:
		{
			_rightPaddlePtr->stop( direction );
			break;
		}
		default:
		{
			// Do nothing;
		}
	}
}


//
// getPaddleWidth()
//
float tModel::getPaddleWidth()
{
	return _paddleWidth;
}


//
// getPaddleHeight()
//
float tModel::getPaddleHeight()
{
	return _paddleHeight;
}


//
// getBallPosition()
//
CGPoint tModel::getBallPosition()
{
	return _ballPtr->getCurrentPosition();
}


//
// getBallRadius()
//
float tModel::getBallRadius()
{
	return _ballRadius;
}


//
// getWallPosition()
//
CGPoint tModel::getWallPosition( const tWallType& wallType )
{
	CGPoint wallPosition;

	switch( wallType )
	{
		case tWallType::kTop:
		{
			wallPosition = _topWallPtr->getPosition();
			break;
		}
		case tWallType::kBottom:
		{
			wallPosition = _bottomWallPtr->getPosition();
			break;
		}
		default:
		{
			// Do nothing;
		}
	}

	return wallPosition;
}


//
// getWallLength()
//
float tModel::getWallLength()
{
	return _topWallPtr->getLength();
}


//
// getWallWidth()
//
float tModel::getWallWidth()
{
	return _wallWidth;
}


//
// getScore()
//
int tModel::getScore( const tPaddle::tPaddleType& player )
{
	int returnVal = 0;

	switch( player )
	{
		case tPaddle::tPaddleType::kLeft:
		{
			returnVal = _leftPlayerScore;
			break;
		}
		case tPaddle::tPaddleType::kRight:
		{
			returnVal = _rightPlayerScore;
			break;
		}
		default:
		{
			// Do nothing.
		}
	}

	return returnVal;
}