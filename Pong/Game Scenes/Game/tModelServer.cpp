#include "tModelServer.h"
#include "../../Game Scenes/Game/tBall.h"
#include "../../Game Scenes/Game/tPaddle.h"
#include "../../Game Scenes/Game/tWall.h"

unsigned int tModelServer::client_id; 

static const int kMaxScore = 5;

static const float kTopWallPositionX = 50.0f;
static const float kTopWallPositionY = 600.0f;

static const float kBottomWallPositionX = 50.0f;
static const float kBottomWallPositionY = 15.0f; // This value should be equal to kWidth defined in tWall.cpp.

static const float kLeftPaddleInitialPositionX = 50.0f;
static const float kLeftPaddleInitialPositionY = 500.0f;

static const float kRightPaddleInitialPositionX = 835.0f;
static const float kRightPaddleInitialPositionY = 500.0f;

//
// constructor()
//
tModelServer::tModelServer()
{
    // id's to assign clients for our table
    client_id = 0;

    // set up the server network to listen 
    network = new ServerNetwork();

	_topWallPtr = new tWall( CGPointMake( kTopWallPositionX, kTopWallPositionY ) );
	_bottomWallPtr = new tWall( CGPointMake( kBottomWallPositionX, kBottomWallPositionY ) );
	_wallWidth = _topWallPtr->getWidth();

	_leftPaddlePtr = new tPaddle( CGPointMake( kLeftPaddleInitialPositionX, kLeftPaddleInitialPositionY ) );
	_rightPaddlePtr = new tPaddle( CGPointMake( kRightPaddleInitialPositionX, kRightPaddleInitialPositionY ) );
	_paddleWidth = _leftPaddlePtr->getWidth();
	_paddleHeight = _leftPaddlePtr->getHeight();

	_ballPtr = new tBall();
	_ballRadius = _ballPtr->getRadius();

	_leftPlayerScore = 0;
	_rightPlayerScore = 0;
}


//
// destructor()
//
tModelServer::~tModelServer(void)
{
    delete _ballPtr;
    _ballPtr = NULL;

	delete _rightPaddlePtr;
	_rightPaddlePtr = NULL;

	delete _leftPaddlePtr;
	_leftPaddlePtr = NULL;

	delete _bottomWallPtr;
	_bottomWallPtr = NULL;

	delete _topWallPtr;
	_topWallPtr = NULL;
}


//
// start()
//
void tModelServer::start()
{
	_leftPlayerScore = 0;
	_rightPlayerScore = 0;

	_ballPtr->start();
}


//
// update()
//
void tModelServer::update( int deltaInMilliseconds )
{
	// get new clients
	if( network->acceptNewClient( client_id ) )
	{
		// If both clients have connected to the server, send the 'START_GAME'
		// packet to the clients.
		if( client_id == 1)
		{
			sendStartGamePacket();
		}

		printf( "client %d has been connected to the server\n", client_id );
        client_id++;
	}

	if( client_id == 2 )
	{
		sendBallPositionPacket( deltaInMilliseconds );
	}

	receiveFromClients();
}


//
// receiveFromClients()
//
void tModelServer::receiveFromClients()
{
    Packet packet;

    // go through all clients
    std::map<unsigned int, SOCKET>::iterator iter;

    for(iter = network->sessions.begin(); iter != network->sessions.end(); iter++)
    {
        int data_length = network->receiveData(iter->first, network_data);

        if (data_length <= 0) 
        {
            //no data recieved
            continue;
        }

        int i = 0;
        while (i < (unsigned int)data_length) 
        {
            packet.deserialize(&(network_data[i]));
            i += sizeof(Packet);

            switch( packet.packet_type )
            {
				case RIGHT_PADDLE_POSITION:
				{
				    CGPoint position;
				    position.x = packet.rightPaddlePositionX;
				    position.y = packet.rightPaddlePositionY;
				    _rightPaddlePtr->setCurrentPosition( position );
                    sendRightPaddlePositionPacket();
                    break;
				}
				case LEFT_PADDLE_POSITION:
				{
				    CGPoint position;
				    position.x = packet.leftPaddlePositionX;
				    position.y = packet.leftPaddlePositionY;
				    _leftPaddlePtr->setCurrentPosition( position );
                    sendLeftPaddlePositionPacket();
                    break;
				}
				default:
				{
                    // Do nothing.
				}
            }
        }
    }
}


//
// sendStartGamePacket()
//
void tModelServer::sendStartGamePacket()
{
    // send action packet
    const unsigned int packet_size = sizeof(Packet);
    char packet_data[packet_size];

    Packet packet;
    packet.packet_type = START_GAME;

    packet.serialize(packet_data);

    network->sendToAll( packet_data, packet_size );
}


//
// sendBallPositionPacket()
//
void tModelServer::sendBallPositionPacket( int deltaInMilliseconds )
{
	if( ( _leftPlayerScore < kMaxScore ) && ( _rightPlayerScore < kMaxScore ) )
	{
		_ballPtr->updatePosition( deltaInMilliseconds );

		// First, detect if the ball collides with the right paddle.
		// Then, detect if the ball collides with the left paddle.
	
		if( ( _ballPtr->intersects( CGRectMake( _rightPaddlePtr->getCurrentPosition().x, _rightPaddlePtr->getCurrentPosition().y, _paddleWidth, _paddleHeight ) ) == true ) &&
			( _ballPtr->getCurrentDirection().x > 0.0f ) )
		{
			_ballPtr->setCurrentPositionX( _rightPaddlePtr->getCurrentPosition().x - _ballRadius );

			// Change the sign of the x-component of the velocity vector and increase the velocity of the ball each time it collides with a paddle.
			_ballPtr->setCurrentDirection( CGPointMake( -_ballPtr->getCurrentDirection().x * 1.2f, _ballPtr->getCurrentDirection().y * 1.2f ) );
		}
		else if( ( _ballPtr->intersects( CGRectMake( _leftPaddlePtr->getCurrentPosition().x, _leftPaddlePtr->getCurrentPosition().y, _paddleWidth, _paddleHeight ) ) == true ) &&
				 ( _ballPtr->getCurrentDirection().x < 0.0f ) )
		{
			_ballPtr->setCurrentPositionX( _leftPaddlePtr->getCurrentPosition().x + _paddleWidth + _ballRadius );

			// Change the sign of the x-component of the velocity vector and increase the velocity of the ball each time it collides with a paddle.
			_ballPtr->setCurrentDirection( CGPointMake( -_ballPtr->getCurrentDirection().x * 1.2f, _ballPtr->getCurrentDirection().y * 1.2f ) );
		}

		// Then, detect if the ball collides with the top wall.
		// Then, detect if the ball collides with the bottom wall.
		if( ( _ballPtr->getCurrentPosition().y + _ballRadius ) >= ( 600 - _wallWidth ) )
		{
			_ballPtr->setCurrentPositionY( 600.0f - _wallWidth - _ballRadius );
			_ballPtr->flipDirectionY();
		}
		else if( ( _ballPtr->getCurrentPosition().y - _ballRadius ) <= _wallWidth )
		{
			_ballPtr->setCurrentPositionY( _wallWidth + _ballRadius );
			_ballPtr->flipDirectionY();
		}

		// Detect if the ball leaves the playing field.
		// Case 1: Ball leaves field to the right and left player scores point.
		// Case 2: Ball leaves field to the left and right player scores point.
		if( ( _ballPtr->getCurrentPosition().x - _ballRadius ) >= 900 )
		{
			_ballPtr->reset();
			_leftPlayerScore = _leftPlayerScore + 1;

			sendLeftPlayerScorePacket();
		}
		else if( ( _ballPtr->getCurrentPosition().x + _ballRadius ) <= 0.0 )
		{
			_ballPtr->reset();
			_rightPlayerScore = _rightPlayerScore + 1;

			sendRightPlayerScorePacket();
		}
		else
		{
			// Do nothing since the ball is still in the playing field.
		}
	}

	// send action packet
	const unsigned int packet_size = sizeof( Packet );
	char packet_data[ packet_size ];

	Packet packet;
	packet.packet_type = BALL_POSITION;
	packet.ballPositionX = _ballPtr->getCurrentPosition().x;
	packet.ballPositionY = _ballPtr->getCurrentPosition().y;
	packet.serialize( packet_data );

	network->sendToAll( packet_data, packet_size );
}


//
// sendLeftPlayerScorePacket()
//
void tModelServer::sendLeftPlayerScorePacket()
{
	const unsigned int packet_size = sizeof( Packet );
	char packet_data[ packet_size ];

	Packet packet;
	packet.packet_type = LEFT_PLAYER_SCORE;
	packet.leftPlayerScore = _leftPlayerScore;
	packet.serialize( packet_data );

	network->sendToAll( packet_data, packet_size );
}


//
// sendRightPlayerScorePacket()
//
void tModelServer::sendRightPlayerScorePacket()
{
	// send action packet
	const unsigned int packet_size = sizeof( Packet );
	char packet_data[ packet_size ];

	Packet packet;
	packet.packet_type = RIGHT_PLAYER_SCORE;
	packet.rightPlayerScore = _rightPlayerScore;
	packet.serialize( packet_data );

	network->sendToAll( packet_data, packet_size );
}


//
// sendLeftPaddlePositionPacket()
//
void tModelServer::sendLeftPaddlePositionPacket()
{
	// send action packet
	const unsigned int packet_size = sizeof( Packet );
	char packet_data[ packet_size ];

	Packet packet;
	packet.packet_type = LEFT_PADDLE_POSITION;
	packet.leftPaddlePositionX = _leftPaddlePtr->getCurrentPosition().x;
	packet.leftPaddlePositionY = _leftPaddlePtr->getCurrentPosition().y;
	packet.serialize( packet_data );

	network->sendToAll( packet_data, packet_size );
}


//
// sendRightPaddlePositionPacket()
//
void tModelServer::sendRightPaddlePositionPacket()
{
	// send action packet
	const unsigned int packet_size = sizeof( Packet );
	char packet_data[ packet_size ];

	Packet packet;
	packet.packet_type = RIGHT_PADDLE_POSITION;
	packet.rightPaddlePositionX = _rightPaddlePtr->getCurrentPosition().x;
	packet.rightPaddlePositionY = _rightPaddlePtr->getCurrentPosition().y;
	packet.serialize( packet_data );

	network->sendToAll( packet_data, packet_size );
}