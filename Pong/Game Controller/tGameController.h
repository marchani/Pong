//
// tGameController.h
//

#ifndef ___TGAMECONTROLLER_H___
#define ___TGAMECONTROLLER_H___

#include <vector>
#include "../Global Headers/tGameSceneType.h"

class iModelAdapter;
class tGameScene;

//
// tGameController
//
class tGameController
{
	public:

		// constructor()
		tGameController();

		// destructor()
		~tGameController();

		// setInstancePtr()
		static void setInstancePtr( tGameController* instancePtr );

		// displayWrapper()
		static void displayWrapper();

		// keyPressedWrapper()
		static void keyPressedWrapper( unsigned char key, int x, int y );

		// keyboardUpWrapper()
		static void keyboardUpWrapper( unsigned char key, int x, int y );

		// start()
		void start();

		// display()
		void display();

		// keyPressed()
		void keyPressed( unsigned char key, int x, int y );

		// keyboardUp()
		void keyboardUp( unsigned char key, int x, int y );

	protected:

		static tGameController* _instancePtr;

	private:

		iModelAdapter* _modelPtr; // Pointer to the Model class.
		tGameScene*    _viewPtr;  // Pointer to the View class.

		tGameSceneType _gameSceneType;

};

#endif