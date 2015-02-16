//
// tGameScene.h
//

#ifndef ___TGAMESCENE_H___
#define ___TGAMESCENE_H___

#include "../../Global Headers/tStructures.h"

class iModelAdapter;
class tBitmapFont;
class tImage;
class tImageRenderManager;
class tTextureManager;

//
// tGameScene
//
class tGameScene
{
	public:

		// constructor()
		tGameScene( iModelAdapter* modelAdapterPtr );

		// destructor()
		~tGameScene();

		// start()
		void start();

		// displayTitleScene()
		virtual void displayTitleScene();

		// displayMainScene()
		virtual void displayMainScene();

	private:

		// renderWall()
		void renderWall( const CGPoint& wallPosition );

		// renderPaddle()
		void renderPaddle( const CGPoint& paddlePosition );

		// renderBall()
		void renderBall( const CGPoint& ballPosition );

		// renderPlayerScore()
		void renderPlayerScore( const CGPoint& renderPoint, int score );

	private:

		iModelAdapter* _modelAdapterPtr;

		tImageRenderManager* _imageRenderManagerPtr;
		tTextureManager* _textureManagerPtr;

		tImage* _titleImagePtr;
		tBitmapFont* _bitmapFontPtr;

		CGPoint _topWallPosition;     // Position of bottom wall.
		CGPoint _bottomWallPosition;  // Position of bottom wall.
		float   _wallLength;          // Length of the top and bottom walls.
		float   _wallWidth;           // Width of the top and bottom walls.

		float _paddleWidth;   // Width of the left and right paddles.
		float _paddleHeight;  // Height of the left and right paddles

		float _ballRadius;  // Radius of the ball.
};

#endif