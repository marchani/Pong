//
// IModelAdapter.h
//

#ifndef ___IMODELADAPTER_H___
#define ___IMODELADAPTER_H___

#include "tPaddle.h"
#include "../../Global Headers/tGameMode.h"
#include "../../Global Headers/tStructures.h"
#include "../../Global Headers/tWallType.h"

//
// iModelAdapter
//
class iModelAdapter
{
	public:

		// getWallPosition()
		virtual CGPoint getWallPosition( const tWallType& wallType ) = 0;

		// getWallLength()
		virtual float getWallLength() = 0;

		// getWallWidth()
		virtual float getWallWidth() = 0;

		// getPaddlePosition()
		virtual CGPoint getPaddlePosition( const tPaddle::tPaddleType& paddleType ) = 0;

		// getPaddleWidth()
		virtual float getPaddleWidth() = 0;

		// getPaddleHeight()
		virtual float getPaddleHeight() = 0;

		// getBallPosition()
		virtual CGPoint getBallPosition() = 0;

		// getBallRadius()
		virtual float getBallRadius() = 0;

		// getScore()
		virtual int getScore( const tPaddle::tPaddleType& player ) = 0;

		// start()
		virtual void start( tGameMode gameMode ) = 0;

		// stop()
		virtual void stop() = 0;

		// update()
		virtual void update( int deltaInMilliseconds ) = 0;

		// movePaddle()
		virtual void movePaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction ) = 0;

		// stopPaddle()
		virtual void stopPaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction ) = 0;
};

#endif