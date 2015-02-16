//
// tGameScene.cpp
//

#include "tGameScene.h"

#include <assert.h>
#include <gl/glut.h>
#include "IModelAdapter.h"
#include "../../Game Engine/Bitmap Font/tBitmapFont.h"
#include "../../Game Engine/Image/tImage.h"
#include "../../Game Engine/Managers/Image Render Manager/tImageRenderManager.h"
#include "../../Game Engine/Managers/Texture Manager/tTextureManager.h"
#include "../../Game Engine/Sprite Sheet/tSpriteSheet.h"

static const int kMaxScore = 5;

//
// constructor()
//
tGameScene::tGameScene( iModelAdapter* modelAdapterPtr )
{
	assert( modelAdapterPtr != NULL );

	_modelAdapterPtr = modelAdapterPtr;

	_imageRenderManagerPtr = new tImageRenderManager();
	_textureManagerPtr = new tTextureManager();

	glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize( 900, 600 );
	glutInitWindowPosition ( 100, 100 );
	glutCreateWindow( "Pong" );

	tSpriteSheet* spriteSheetPtr = new tSpriteSheet( _imageRenderManagerPtr, _textureManagerPtr, "Logo.tga", tTextureManager::kImageFileFormat::kTGA );
	_titleImagePtr = spriteSheetPtr->spriteImageAtCoords( CGPointMake( 0, 0 ) );
	_titleImagePtr->setFlipVertical( true );

	_bitmapFontPtr = new tBitmapFont( _imageRenderManagerPtr, _textureManagerPtr, "LevenimMT.png", "LevenimMT.fnt" );

	// Query the parameters of the model that will not change during the lifetime of the game for improved performance.
	_topWallPosition = _modelAdapterPtr->getWallPosition( tWallType::kTop );
	_bottomWallPosition = _modelAdapterPtr->getWallPosition( tWallType::kBottom );
	_wallLength = _modelAdapterPtr->getWallLength();
	_wallWidth = _modelAdapterPtr->getWallWidth();

	_paddleWidth = _modelAdapterPtr->getPaddleWidth();
	_paddleHeight = _modelAdapterPtr->getPaddleHeight();

	_ballRadius = _modelAdapterPtr->getBallRadius();

	// Configure basic OpenGL settings.
	glOrtho( 0, 900, 0, 600, -1, 1 );
}


//
// destructor()
//
tGameScene::~tGameScene()
{
	delete _bitmapFontPtr;
	_bitmapFontPtr = NULL;

	delete _textureManagerPtr;
	_textureManagerPtr = NULL;

	delete _imageRenderManagerPtr;
	_imageRenderManagerPtr = NULL;
}


//
// start()
//
void tGameScene::start()
{
	glutMainLoop();
}


//
// renderWall()
//
void tGameScene::renderWall( const CGPoint& wallPosition )
{
	glColor3f( 0xFF, 0xFF, 0xFF );
    glVertex2f( wallPosition.x, wallPosition.y );
    glVertex2f( wallPosition.x, wallPosition.y - _wallWidth );
	glVertex2f( wallPosition.x + _wallLength, wallPosition.y - _wallWidth );
    glVertex2f( wallPosition.x + _wallLength, wallPosition.y );
}


//
// renderPaddle()
//
void tGameScene::renderPaddle( const CGPoint& paddlePosition )
{
	glColor3f( 0xFF, 0xFF, 0xFF );
    glVertex2f( paddlePosition.x, paddlePosition.y );
    glVertex2f( paddlePosition.x, paddlePosition.y - _paddleHeight );
	glVertex2f( paddlePosition.x + _paddleWidth, paddlePosition.y - _paddleHeight );
    glVertex2f( paddlePosition.x + _paddleWidth, paddlePosition.y );
}


//
// renderBall()
//
void tGameScene::renderBall( const CGPoint& ballPosition )
{
	glVertex2f( ballPosition.x, ballPosition.y );
 
	for( float angle = 1.0f; angle < 361.0f; angle += 0.2f)
	{
		float x2 = ballPosition.x + sin( angle ) * _ballRadius;
		float y2 = ballPosition.y + cos( angle ) * _ballRadius;
		glVertex2f( x2, y2 );
	}
}


//
// renderPlayerScore()
//
void tGameScene::renderPlayerScore( const CGPoint& renderPoint, int score )
{
	const float width = 50.0f;
	const float midHeight = 40.0f;

	if( score == 0 )
	{
		glBegin( GL_LINE_STRIP );
		glVertex2f( renderPoint.x + width, renderPoint.y );
		glVertex2f( renderPoint.x, renderPoint.y );
		glVertex2f( renderPoint.x, renderPoint.y - ( 2 * midHeight ) );
		glVertex2f( renderPoint.x + width, renderPoint.y - ( 2 * midHeight ) );
		glVertex2f( renderPoint.x + width, renderPoint.y );
		glEnd();
	}
	else if( score == 1 )
	{
		glBegin( GL_LINES );
		glVertex2f( renderPoint.x + width, renderPoint.y );
		glVertex2f( renderPoint.x + width, renderPoint.y - ( 2 * midHeight ) );
		glEnd();
	}
	else if( score == 2 )
	{
		glBegin( GL_LINE_STRIP );
		glVertex2f( renderPoint.x, renderPoint.y );
		glVertex2f( renderPoint.x + width, renderPoint.y );
		glVertex2f( renderPoint.x + width, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x, renderPoint.y - ( 2 * midHeight ) );
		glVertex2f( renderPoint.x + width, renderPoint.y - ( 2 * midHeight ) );
		glEnd();
	}
	else if( score == 3 )
	{
		glBegin( GL_LINE_STRIP );
		glVertex2f( renderPoint.x, renderPoint.y );
		glVertex2f( renderPoint.x + width, renderPoint.y );
		glVertex2f( renderPoint.x + width, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x + width, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x + width, renderPoint.y - ( 2 * midHeight ) );
		glVertex2f( renderPoint.x, renderPoint.y - ( 2 * midHeight ) );
		glEnd();
	}
	else if( score == 4 )
	{
		glBegin( GL_LINE_STRIP );
		glVertex2f( renderPoint.x, renderPoint.y );
		glVertex2f( renderPoint.x, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x + width, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x + width, renderPoint.y );
		glVertex2f( renderPoint.x + width, renderPoint.y - ( 2 * midHeight ) );
		glEnd();
	}
	else if( score == 5 )
	{
		glBegin( GL_LINE_STRIP );
		glVertex2f( renderPoint.x + width, renderPoint.y );
		glVertex2f( renderPoint.x, renderPoint.y );
		glVertex2f( renderPoint.x, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x + width, renderPoint.y - midHeight );
		glVertex2f( renderPoint.x + width, renderPoint.y - ( 2 * midHeight ) );
		glVertex2f( renderPoint.x, renderPoint.y - ( 2 * midHeight ) );
		glEnd();
	}
}


//
// displayMainScene()
//
void tGameScene::displayMainScene()
{
	assert( _modelAdapterPtr != NULL );
	assert( _bitmapFontPtr != NULL );
	assert( _imageRenderManagerPtr != NULL );

    // Clear the screen and set our initial view matrix
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	glDisable( GL_TEXTURE_2D );

	// Draw the walls and paddles.
	glBegin( GL_QUADS );
	renderWall( _topWallPosition );
	renderWall( _bottomWallPosition );
	renderPaddle( _modelAdapterPtr->getPaddlePosition( tPaddle::tPaddleType::kLeft ) );
	renderPaddle( _modelAdapterPtr->getPaddlePosition( tPaddle::tPaddleType::kRight ) );
    glEnd();

	// Draw the ball.
	glBegin( GL_TRIANGLE_FAN );
	renderBall( _modelAdapterPtr->getBallPosition() ); 
	glEnd();

	int leftPlayerScore = _modelAdapterPtr->getScore( tPaddle::tPaddleType::kLeft );
	int rightPlayerScore = _modelAdapterPtr->getScore( tPaddle::tPaddleType::kRight );

	renderPlayerScore( CGPointMake( 370.0f, 555.0f ), leftPlayerScore );
	renderPlayerScore( CGPointMake( 480.0f, 555.0f ), rightPlayerScore );

	if( _modelAdapterPtr->getScore( tPaddle::tPaddleType::kLeft ) == kMaxScore )
	{
		glEnable( GL_TEXTURE_2D );
		_bitmapFontPtr->renderStringAt( CGPointMake( 353.0f, 135.0f ), "Left Player Wins" );
		_bitmapFontPtr->renderStringAt( CGPointMake( 240.0f, 95.0f ), "Press 'Q' to return to the title screen" );
		_imageRenderManagerPtr->renderImages();
		glDisable( GL_TEXTURE_2D );
	}
	else if( rightPlayerScore == kMaxScore )
	{
		glEnable( GL_TEXTURE_2D );
		_bitmapFontPtr->renderStringAt( CGPointMake( 348.0f, 135.0f ), "Right Player Wins" );
		_bitmapFontPtr->renderStringAt( CGPointMake( 240.0f, 95.0f ), "Press 'Q' to return to the title screen" );
		_imageRenderManagerPtr->renderImages();
		glDisable( GL_TEXTURE_2D );
	}

	// We just drew to the back buffer.  Now we need to swap that with the
    // front buffer to show it on screen.
    glutSwapBuffers();
}


//
// displayTitleScene()
//
void tGameScene::displayTitleScene()
{
	assert( _titleImagePtr != NULL );
	assert( _bitmapFontPtr != NULL );
	assert( _imageRenderManagerPtr != NULL );

    // Clear the screen and enable textures.
    glClear( GL_COLOR_BUFFER_BIT );
	glEnable( GL_TEXTURE_2D );

	_titleImagePtr->renderCenteredAtPoint( CGPointMake( 450.0f, 375.0f ), Scale2fMake( 1.2, 1.2 ) );
	_bitmapFontPtr->renderStringAt( CGPointMake( 380.0f, 205.0f ), Color4fMake( 0.4f, 0.4f, 0.4f, 0.0f ), "One Player" );
	_bitmapFontPtr->renderStringAt( CGPointMake( 335.0f, 165.0f ), "Two Players (Local)" );
	_bitmapFontPtr->renderStringAt( CGPointMake( 320.0f, 125.0f ), Color4fMake( 0.4f, 0.4f, 0.4f, 0.0f ), "Two Players (Network)" );
	_bitmapFontPtr->renderStringAt( CGPointMake( 245.0f, 50.0f ), "Press spacebar to make selection" );

	_imageRenderManagerPtr->renderImages();

	// We just drew to the back buffer.  Now we need to swap that with the
    // front buffer to show it on screen.
    glutSwapBuffers();
}