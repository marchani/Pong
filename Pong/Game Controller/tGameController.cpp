//
// tGameController.cpp
//

#include "tGameController.h"

#include <assert.h>
#include <gl/glut.h>
#include <process.h>
#include <sys/timeb.h>
#include "../Game Scenes/Game/tModelServer.h"
#include "../Game Scenes/Game/tGameScene.h"
#include "../Game Scenes/Game/tModel.h"
#include "../Game Scenes/Game/tModelClient.h"
#include "../Global Headers/tGameMode.h"

tGameController* tGameController::_instancePtr = NULL;

static const float kRefreshRateInMilliseconds = ( 1.0f / 60.0f /* Hz */) / 1000.0f /* milliseconds per second */;
static const float kRefreshRateInMillisecondsServer = 5.0f;

timeb gTimestamp;
timeb gTimestampServer;

tModelServer* serverPtr;
tModelClient* client;

void serverLoop( void* );

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
	glutSpecialFunc( specialKeyPressedWrapper );
	glutKeyboardUpFunc( keyboardUpWrapper );

	// Initialize the global timestamp used when refreshing the screen.
	ftime( &gTimestamp );
	ftime( &gTimestampServer );
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
// specialKeyPressedWrapper()
//
void tGameController::specialKeyPressedWrapper( int key, int x, int y )
{
	if( _instancePtr != NULL )
	{
		_instancePtr->specialKeyPressed( key, x, y );
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

	if( client != NULL )
	{
		client->update( timeSinceLastCall );

		if( client->getStartGame() == true )
		{
			_gameSceneType = tGameSceneType::kMainScene;
			_modelPtr->start( tGameMode::kMultiPlayerNetwork );
		}
	}

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
			case tGameSceneType::kNetworkScene:
			{
				_viewPtr->displayNetworkScene();
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
	assert( _viewPtr != NULL );

	switch( _gameSceneType )
	{
		case tGameSceneType::kTitleScene:
		{
			switch( key )
			{
				case 32 /* spacebar */:
				{
					int currentSelection = _viewPtr->getCurrentSelection();

					if( currentSelection == 0 )
					{
						_gameSceneType = tGameSceneType::kMainScene;
						_modelPtr->start( tGameMode::kSinglePlayer );
					}
					else if( currentSelection == 1 )
					{
						_gameSceneType = tGameSceneType::kMainScene;
						_modelPtr->start( tGameMode::kMultiPlayerLocal );
					}
					else if( currentSelection == 2 )
					{
						_gameSceneType = tGameSceneType::kNetworkScene;
					}
					break;
				}
				default:
				{
					// Do nothing.
				}
			}
			break;
		}
		case tGameSceneType::kNetworkScene:
		{
			switch( key )
			{
				case 32 /* spacebar */:
				{
					int currentSelection = _viewPtr->getCurrentSelectionNetwork();

					if( currentSelection == 0 )
					{
						if( serverPtr == NULL )
						{
							// Create the game server.
							serverPtr = new tModelServer();

							// create thread with arbitrary argument for the run function
							_beginthread( serverLoop, 0, (void*)12);
						}

						if( client == NULL )
						{
							// Create the game client.
							client = new tModelClient( _modelPtr, tPaddle::tPaddleType::kRight );
						}
					}
					else if( currentSelection == 1 )
					{
						// Create the game client.
						client = new tModelClient( _modelPtr, tPaddle::tPaddleType::kLeft );
					}
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
// specialKeyPressed()
//
void tGameController::specialKeyPressed( int key, int x, int y )
{
	assert( _modelPtr != NULL );
	assert( _viewPtr != NULL );

	switch( _gameSceneType )
	{
		case tGameSceneType::kTitleScene:
		{
			switch( key )
			{
				case 101: /* up */
				{
					_viewPtr->moveSelection( tGameScene::tDirection::kUp );
					break;
				}
				case 103: /* down */
				{
					_viewPtr->moveSelection( tGameScene::tDirection::kDown );
					break;
				}
				default:
				{
					// Do nothing.
					break;
				}
			}
			break;
		}
		case tGameSceneType::kNetworkScene:
		{
			switch( key )
			{
				case 101: /* up */
				{
					_viewPtr->moveSelectionNetwork( tGameScene::tDirection::kUp );
					break;
				}
				case 103: /* down */
				{
					_viewPtr->moveSelectionNetwork( tGameScene::tDirection::kDown );
					break;
				}
				default:
				{
					// Do nothing.
					break;
				}
			}
			break;
		}
		default:
		{
			// Do nothing.
			break;
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
// serverLoop()
//
void serverLoop( void* arg)
{
	serverPtr->start();

    while( true )
    {
		// Obtain the number of milliseconds since this function was last called.
		timeb currentTime;
		ftime( &currentTime );
		int timeSinceLastCall = ( int )( 1000.0 * ( currentTime.time - gTimestampServer.time ) + ( currentTime.millitm - gTimestampServer.millitm ) );

		// Refresh the screen based on the desired refresh rate (kRefreshRateInMilliseconds).
		if(  timeSinceLastCall >= kRefreshRateInMillisecondsServer )
		{
			// Update the global timestamp used when refreshing the screen.
			gTimestampServer = currentTime;

			assert( serverPtr != NULL );
			serverPtr->update( timeSinceLastCall );
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