//
// tPaddle.cpp
//

#include "tPaddle.h"

static const float kWidth = 15.0f;
static const float kHeight = 125.0f;

//
// constructor
//
tPaddle::tPaddle( CGPoint startingPosition )
{
	_startingPosition = startingPosition;
	_currentPosition = startingPosition;
	_width = kWidth;
	_height = kHeight;
	_isMovingUp = false;
	_isMovingDown = false;
}


//
// destructor
//
tPaddle::~tPaddle()
{
}


//
// reset()
//
void tPaddle::reset()
{
	_currentPosition = _startingPosition;
}


//
// getCurrentPosition()
//
CGPoint tPaddle::getCurrentPosition()
{
	return _currentPosition;
}


//
// getWidth()
//
float tPaddle::getWidth()
{
	return _width;
}


//
// getHeight()
//
float tPaddle::getHeight()
{
	return _height;
}


//
// move()
//
void tPaddle::move( tDirection direction )
{
	switch( direction )
	{
		case tDirection::kUp:
		{
			_isMovingUp = true;
			break;
		};
		case tDirection::kDown:
		{
			_isMovingDown = true;
			break;
		}
		default:
		{
			// Do nothing.
		}
	}
}


//
// stop()
//
void tPaddle::stop( tDirection direction )
{
	switch( direction )
	{
		case tDirection::kUp:
		{
			_isMovingUp = false;
			break;
		};
		case tDirection::kDown:
		{
			_isMovingDown = false;
			break;
		}
		default:
		{
			// Do nothing.
		}
	}
}


//
// updatePosition()
//
void tPaddle::updatePosition( int deltaInMilliseconds )
{
	float timeFactor = deltaInMilliseconds / 3.0f;

	if( _isMovingUp == true )
	{
		if( ( _currentPosition.y ) <= ( 600.0f - 15.0f ) )
		{
			_currentPosition.y = _currentPosition.y + timeFactor;
		}
		else // _currentPosition.y > ( 600.0f - 15.0f )
		{
			// Do nothing.
		}
	}

	if( _isMovingDown == true )
	{
		if( ( _currentPosition.y - _height ) >= ( 0.0f + 15.0f ) )
		{
			_currentPosition.y = _currentPosition.y - timeFactor;
		}
		else // _currentPosition.y < ( 0.0f + 15.0f )
		{
			// Do nothing.
		}
	}
}