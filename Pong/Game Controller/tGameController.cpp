//
// tGameController.cpp
//

#include "tGameController.h"

#include <assert.h>
#include <gl/glut.h>
#include <sys/timeb.h>
#include "../Game Scenes/Game/tGameScene.h"
#include "../Game Scenes/Game/tModel.h"

tGameController* tGameController::_instancePtr = NULL;

static const float kRefreshRateInMilliseconds = ( 1.0f / 60.0f /* Hz */) / 1000.0f /* milliseconds per second */;

timeb gTimestamp;

//
// Constructor()
//
tGameController::tGameController()
{
	// Instantiate a model.
	_modelPtr = new tModel();

	// Instantiate a view.
	_viewPtr = new tGameScene( _modelPtr );

	_gameSceneType = tGameSceneType::kTitleScene;

	// Register the wrappers with the event handlers.
	glutDisplayFunc( displayWrapper );
	glutKeyboardFunc( keyPressedWrapper );
	glutKeyboardUpFunc( keyboardUpWrapper );

	// Initialize the global timestamp used when refreshing the screen.
	ftime( &gTimestamp );
}


//
// Destructor()
//
tGameController::~tGameController()
{
	delete _viewPtr;
	_viewPtr = NULL;

	delete _modelPtr;
	_modelPtr = NULL;
}


//
// setInstancePtr()
//
void tGameController::setInstancePtr( tGameController* instancePtr )
{
	_instancePtr = instancePtr;
}


//
// start()
//
void tGameController::start()
{
	if( _viewPtr != NULL )
	{
		_viewPtr->start();
	}
	else // _viewPtr == NULL
	{
		// Do nothing.
	}
}


//
// displayWrapper()
//
void tGameController::displayWrapper()
{
	if( _instancePtr != NULL )
	{
		_instancePtr->display();
	}
	else // _instancePtr == NULL
	{
		// Do nothing.
	}
}


//
// keyPressedWrapper()
//
void tGameController::keyPressedWrapper( unsigned char key, int x, int y )
{
	if( _instancePtr != NULL )
	{
		_instancePtr->keyPressed( key, x, y );
	}
	else // _instancePtr == NULL
	{
		// Do nothing.
	}
}


//
// keyboardUpWrapper()
//
void tGameController::keyboardUpWrapper( unsigned char key, int x, int y )
{
	if( _instancePtr != NULL )
	{
		_instancePtr->keyboardUp( key, x, y );
	}
	else // _instancePtr == NULL
	{
		// Do nothing.
	}
}


//
// display()
//
void tGameController::display()
{
	assert( _modelPtr != NULL );
	assert( _viewPtr != NULL );

	// Obtain the number of milliseconds since this function was last called.
	timeb currentTime;
	ftime( &currentTime );
	int timeSinceLastCall = ( int )( 1000.0 * ( currentTime.time - gTimestamp.time ) + ( currentTime.millitm - gTimestamp.millitm ) );

	// Update the model.
	_modelPtr->update( timeSinceLastCall );

	// Refresh the screen based on the desired refresh rate (kRefreshRateInMilliseconds).
	if(  timeSinceLastCall >= kRefreshRateInMilliseconds )
	{
		// Update the global timestamp used when refreshing the screen.
		gTimestamp = currentTime;

		switch( _gameSceneType )
		{
			case tGameSceneType::kTitleScene:
			{
				_viewPtr->displayTitleScene();
				break;
			}
			case tGameSceneType::kMainScene:
			{
				_viewPtr->displayMainScene();
				break;
			}
			default:
			{
				// Do nothing.
			}
		}
	}
	else // timeSinceLastCall < kRefreshRateInMilliseconds
	{
		// Do nothing.
	}

	glutPostRedisplay();
}


//
// keyPressed()
//
void tGameController::keyPressed( unsigned char key, int x, int y )
{
	assert( _modelPtr != NULL );

	switch( _gameSceneType )
	{
		case tGameSceneType::kTitleScene:
		{
			switch( key )
			{
				case 32 /* spacebar */:
				{
					_gameSceneType = tGameSceneType::kMainScene;
					_modelPtr->start();
					break;
				}
				default:
				{
					// Do nothing.
				}
			}
			break;
		}
		case tGameSceneType::kMainScene:
		{
			switch( key )
			{
				case 'a':
				{
					_modelPtr->movePaddle( tPaddle::tPaddleType::kLeft, tPaddle::tDirection::kUp );
					break;
				}
				case 'z':
				{
					_modelPtr->movePaddle( tPaddle::tPaddleType::kLeft, tPaddle::tDirection::kDown );
					break;
				}
				case 39:
				{
					_modelPtr->movePaddle( tPaddle::tPaddleType::kRight, tPaddle::tDirection::kUp );
					break;
				}
				case '/':
				{
					_modelPtr->movePaddle( tPaddle::tPaddleType::kRight, tPaddle::tDirection::kDown );
					break;
				}
				case 'q':
				{
					_modelPtr->stop();
					_gameSceneType = tGameSceneType::kTitleScene;
					break;
				}
				default:
				{
					// Do nothing.
				}
			}
			break;
		}
		default:
		{
			// Do nothing.
		}
	}
}


//
// keyboardUp()
//
void tGameController::keyboardUp( unsigned char key, int x, int y )
{
	assert( _modelPtr != NULL );

	switch( _gameSceneType )
	{
		case tGameSceneType::kTitleScene:
		{
			// Do nothing.
			break;
		}
		case tGameSceneType::kMainScene:
		{
			switch( key )
			{
				case 'a':
				{
					_modelPtr->stopPaddle( tPaddle::tPaddleType::kLeft, tPaddle::tDirection::kUp );
					break;
				}
				case 'z':
				{
					_modelPtr->stopPaddle( tPaddle::tPaddleType::kLeft, tPaddle::tDirection::kDown );
					break;
				}
				case 39:
				{
					_modelPtr->stopPaddle( tPaddle::tPaddleType::kRight, tPaddle::tDirection::kUp );
					break;
				}
				case '/':
				{
					_modelPtr->stopPaddle( tPaddle::tPaddleType::kRight, tPaddle::tDirection::kDown );
					break;
				}
				default:
				{
					// Do nothing.
				}
			}
			break;
		}
		default:
		{
			// Do nothing.
		}
	}
}


//
// main()
//
int main( int argc, char** argv )
{
	// Instantiate a tGameController to start the Model-View-Controller Framework.
	tGameController controller;
	controller.setInstancePtr( &controller );
	controller.start();

	return 0;
}