#pragma once
#include <string.h>

#define MAX_PACKET_SIZE 1000000


//
// PacketTypes
//
enum PacketTypes
{
//    INIT_CONNECTION = 0,
	START_GAME = 1,
	BALL_POSITION = 2,
	LEFT_PADDLE_POSITION = 3,
	RIGHT_PADDLE_POSITION = 4,
	LEFT_PLAYER_SCORE = 5,
	RIGHT_PLAYER_SCORE = 6,
};


//
// Packet()
//
struct Packet
{
    unsigned int packet_type;

	float ballPositionX;
	float ballPositionY;
	float leftPaddlePositionX;
	float leftPaddlePositionY;
	float rightPaddlePositionX;
	float rightPaddlePositionY;
	int leftPlayerScore;
	int rightPlayerScore;
	int client_id;

    void serialize( char* data )
	{
        memcpy(data, this, sizeof(Packet));
    }

    void deserialize( char* data )
	{
        memcpy(this, data, sizeof(Packet));
    }
};