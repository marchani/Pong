#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "../../Game Engine/Network/ClientNetwork.h"
#include "../../Game Engine/Network/NetworkData.h"
#include "../../Game Scenes/Game/tPaddle.h"

class iModelAdapter;

//
// tModelClient()
//
class tModelClient
{
	public:

		// constructor()
		tModelClient( iModelAdapter* modelAdapterPtr, tPaddle::tPaddleType paddleType );

		// destructor()
		~tModelClient();

		// getStartGame()
		bool getStartGame();

		// getScore()
		int getScore( const tPaddle::tPaddleType& player );

		// movePaddle()
		void movePaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction );

		// stopPaddle()
		void stopPaddle( tPaddle::tPaddleType paddleType, tPaddle::tDirection direction );

		// sendPaddlePositionPackets()
		void sendPaddlePositionPackets();

		// update()
		void update( int deltaInMilliseconds );

		ClientNetwork* network;

		char network_data[ MAX_PACKET_SIZE ];

	private:

		int _leftPlayerScore;
		int _rightPlayerScore;

		iModelAdapter* _modelAdapterPtr;

		bool _startGame;

		tPaddle::tPaddleType _paddleType;
};

