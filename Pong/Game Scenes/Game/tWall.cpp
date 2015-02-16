//
// tWall.cpp
//

#include "tWall.h"

static const float kWidth = 15.0f;
static const float kLength = 800.0f;

//
// constructor()
//
tWall::tWall( CGPoint position )
{
	_position = position;
}


//
// destructor()
//
tWall::~tWall()
{
}


//
// getPosition()
//
CGPoint tWall::getPosition()
{
	return _position;
}

//
// getLength()
//
float tWall::getLength()
{
	return kLength;
}


//
// getWidth()
//
float tWall::getWidth()
{
	return kWidth;
}