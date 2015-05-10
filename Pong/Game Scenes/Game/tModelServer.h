//
// tModelServer.h
//

#pragma once
#include "../../Game Engine/Network/ServerNetwork.h"
#include "../../Game Engine/Network/NetworkData.h"

class tBall;
class tPaddle;
class tWall;

//
// tModelServer
//
class tModelServer
{
	public:

		// constructor()
	    tModelServer();

		// destructor()
		~tModelServer();

		// start()
		void start();

		// update()
	    void update( int deltaInMilliseconds );

		// receiveFromClients()
		void receiveFromClients();

		// sendStartGamePacket()
		void sendStartGamePacket();

		// sendBallPositionPacket()
		void sendBallPositionPacket( int deltaInMilliseconds );

		// sendLeftPlayerScorePacket()
		void sendLeftPlayerScorePacket();

		// sendLeftPaddlePositionPacket()
		void sendLeftPaddlePositionPacket();

		// sendRightPlayerScorePacket()
		void sendRightPlayerScorePacket();

		// sendRightPaddlePositionPacket()
		void sendRightPaddlePositionPacket();

	private:

        tWall* _topWallPtr;
        tWall* _bottomWallPtr;
		tPaddle* _leftPaddlePtr;
		tPaddle* _rightPaddlePtr;
		tBall*  _ballPtr;

        float _wallWidth;     // Width of the top and bottom walls.
		float _paddleWidth;   // Width of the left and right paddles.
		float _paddleHeight;  // Height of the left and right paddles.
		float _ballRadius;    // Radius of the ball.

		int _leftPlayerScore;
		int _rightPlayerScore;

		// IDs for the clients connecting for table in ServerNetwork 
		static unsigned int client_id;

		// The ServerNetwork object
		ServerNetwork* network;

		// data buffer
		char network_data[ MAX_PACKET_SIZE ];
};