//
// tBall.h
//

#ifndef ___TBALL_H___
#define ___TBALL_H___

#include "../../Global Headers/tStructures.h"

//
// tBall
//
class tBall
{
	public:

		// constructor()
		tBall();

		// destructor()
		~tBall();

		// getCurrentDirection()
		CGPoint getCurrentDirection();

		// setCurrentDirection()
		void setCurrentDirection( const CGPoint& direction );

		// getCurrentPosition()
		CGPoint getCurrentPosition();

		// setCurrentPosition()
		void setCurrentPosition( const CGPoint& position );

		// setCurrentPositionX()
		void setCurrentPositionX( float x );

		// setCurrentPositionY()
		void setCurrentPositionY( float y );

		// getRadius()
		float getRadius();

		// changeSpeed()
		void changeSpeed( float factor );

		// start()
		void start();

		// stop()
		void stop();

		// reset()
		void reset();

		// updatePosition()
		void updatePosition( int deltaInMilliseconds );

		// flipDirectionX()
		void flipDirectionX();

		// flipDirectionY()
		void flipDirectionY();

	public:

		// intersects
		bool intersects( const CGRect& rectangularObject );

	private:

		CGPoint _startingPosition;
		CGPoint _currentPosition;
		CGPoint _currentDirection;
};

#endif