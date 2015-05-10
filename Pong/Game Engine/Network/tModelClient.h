#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "ClientNetwork.h"
#include "NetworkData.h"
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

