//
// tModel.h
//

#ifndef ___TMODEL___
#define ___TMODEL___

#include "IModelAdapter.h"

#include <vector>
#include "../../Global Headers/tStructures.h"
#include "../../Global Headers/tWallType.h"

class tBall;
class tPaddle;
class tWall;

//
// tModel
//
class tModel : public iModelAdapter
{
	public:

		// constructor()
		tModel();

		// destructor()
		~tModel();

		// start()
		void start( tGameMode gameMode );

		// stop()
		void stop();

		// update()
		void update( int deltaInMilliseconds );

		// getPaddlePosition()
		CGPoint getPaddlePosition( const tPaddle::tPaddleType& paddleType );

		// movePaddle()
		void movePaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction );

		// stopPaddle()
		void stopPaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction );

		// getPaddleWidth()
		float getPaddleWidth();

		// getPaddleHeight()
		float getPaddleHeight();

		// getBallPosition()
		CGPoint getBallPosition();

		// getBallRadius()
		float getBallRadius();

		// getWallPosition()
		CGPoint getWallPosition( const tWallType& wallType );

		// getWallLength()
		float getWallLength();

		// getWallWidth()
		float getWallWidth();

		// getScore()
		int getScore( const tPaddle::tPaddleType& player );

	private:

		// updateAI()
		void updateAI();

	private:

		tWall*  _topWallPtr;
		tWall*  _bottomWallPtr;
		tPaddle* _leftPaddlePtr;
		tPaddle* _rightPaddlePtr;
		tBall*  _ballPtr;

		float _wallWidth;     // Width of the top and bottom walls.
		float _paddleWidth;   // Width of the left and right paddles.
		float _paddleHeight;  // Height of the left and right paddles.
		float _ballRadius;    // Radius of the ball.

		int _leftPlayerScore;
		int _rightPlayerScore;

		bool _isRunning;

		bool _aiEnabled;  // Is artificial intelligence enabled?
};

#endif