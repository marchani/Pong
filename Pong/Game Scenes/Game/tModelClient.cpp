#include "tModelClient.h"

#include "../../Game Scenes/Game/IModelAdapter.h"


//
// constructor()
//
tModelClient::tModelClient( iModelAdapter* modelAdapterPtr, tPaddle::tPaddleType paddleType )
{
    network = new ClientNetwork();

	int error = network->getError();

	if( error == 0 )
	{
		_modelAdapterPtr = modelAdapterPtr;

		_startGame = false;

		_paddleType = paddleType;
	}
}


//
// destructor()
//
tModelClient::~tModelClient() {}


//
// getStartGame()
//
bool tModelClient::getStartGame()
{
	if( _startGame == true )
	{
		_startGame = false;
		return true;
	}

	return false;
}


//
// getScore()
//
int tModelClient::getScore( const tPaddle::tPaddleType& player )
{
	int returnVal = 0;

	switch( player )
	{
		case tPaddle::tPaddleType::kLeft:
		{
			returnVal = _leftPlayerScore;
			break;
		}
		case tPaddle::tPaddleType::kRight:
		{
			returnVal = _rightPlayerScore;
			break;
		}
		default:
		{
			// Do nothing.
		}
	}

	return returnVal;
}


//
// sendPaddlePositionPackets()
//
void tModelClient::sendPaddlePositionPackets()
{
    const unsigned int packet_size = sizeof( Packet );
    char packet_data[ packet_size ];

	if( _paddleType == tPaddle::tPaddleType::kRight )
	{
		Packet packet;
		packet.packet_type = RIGHT_PADDLE_POSITION;
		packet.rightPaddlePositionX = _modelAdapterPtr->getPaddlePosition( tPaddle::tPaddleType::kRight ).x;
		packet.rightPaddlePositionY = _modelAdapterPtr->getPaddlePosition( tPaddle::tPaddleType::kRight ).y;
		packet.serialize(packet_data);

		NetworkServices::sendMessage( network->ConnectSocket, packet_data, packet_size );
	}
	else
	{
		Packet packet;
		packet.packet_type = LEFT_PADDLE_POSITION;
		packet.leftPaddlePositionX = _modelAdapterPtr->getPaddlePosition( tPaddle::tPaddleType::kLeft ).x;
		packet.leftPaddlePositionY = _modelAdapterPtr->getPaddlePosition( tPaddle::tPaddleType::kLeft ).y;
		packet.serialize( packet_data );

		NetworkServices::sendMessage( network->ConnectSocket, packet_data, packet_size );
	}
}


//
// update()
//
void tModelClient::update( int deltaInMilliseconds )
{
    Packet packet;
    int data_length = network->receivePackets(network_data);

    if (data_length <= 0) 
    {
        //no data recieved
        return;
    }

    int i = 0;
    while (i < (unsigned int)data_length) 
    {
        packet.deserialize(&(network_data[i]));
        i += sizeof(Packet);

        switch( packet.packet_type )
		{
			case START_GAME:
			{
				_startGame = true;
				break;
			}
			case BALL_POSITION:
			{
				CGPoint position;
				position.x = packet.ballPositionX;
				position.y = packet.ballPositionY;
				_modelAdapterPtr->setBallPosition( position );
				break;
			}
			case LEFT_PADDLE_POSITION:
			{
				CGPoint position;
				position.x = packet.leftPaddlePositionX;
				position.y = packet.leftPaddlePositionY; 
				_modelAdapterPtr->setPaddlePosition( tPaddle::tPaddleType::kLeft, position );
				break;
			}	
			case RIGHT_PADDLE_POSITION:
			{
				CGPoint position;
				position.x = packet.rightPaddlePositionX;
				position.y = packet.rightPaddlePositionY; 
				_modelAdapterPtr->setPaddlePosition( tPaddle::tPaddleType::kRight, position );
				break;
			}
			case LEFT_PLAYER_SCORE:
			{
				_leftPlayerScore = packet.leftPlayerScore;
				// TODO: Remove the following line.
				_modelAdapterPtr->setScore( tPaddle::tPaddleType::kLeft, packet.leftPlayerScore );
				break;
			}
			case RIGHT_PLAYER_SCORE:
			{
				_rightPlayerScore = packet.rightPlayerScore;
				// TODO: Remove the following line.
				_modelAdapterPtr->setScore( tPaddle::tPaddleType::kRight, packet.rightPlayerScore );
				break;
			}
            default:
			{
				// Do nothing.
			}
        }
    }

	_modelAdapterPtr->update( deltaInMilliseconds );

	sendPaddlePositionPackets();
}
