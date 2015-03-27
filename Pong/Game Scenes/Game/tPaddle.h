//
// tPaddle.h
//

#ifndef ___TPADDLE_H___
#define ___TPADDLE_H___

#include "../../Global Headers/tStructures.h"

//
// tPaddle
//
class tPaddle
{
	public:

		enum tPaddleType
		{
			kLeft = 0,
			kRight = 1
		};

		enum tDirection
		{
			kUp = 0,
			kDown = 1
		};

		// constructor()
		tPaddle( CGPoint startingPosition );

		// destructor()
		~tPaddle();

		// reset()
		void reset();

		// getCurrentPosition()
		CGPoint getCurrentPosition();

		// getIsMovingUp()
		bool getIsMovingUp() { return _isMovingUp; }

		// getIsMovingDown()
		bool getIsMovingDown() { return _isMovingDown; }

		// getWidth()
		float getWidth();

		// getHeight()
		float getHeight();

		// move()
		void move( tDirection direction );

		// stop()
		void stop( tDirection direction );

		// updatePosition()
		void updatePosition( int deltaInMilliseconds );

	private:

		CGPoint _startingPosition;
		CGPoint _currentPosition;
		float _width;
		float _height;

		bool _isMovingUp;
		bool _isMovingDown;
};

#endif