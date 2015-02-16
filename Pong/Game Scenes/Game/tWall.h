//
// tWall.h
//

#ifndef ___TWALL_H___
#define ___TWALL_H___

#include "../../Global Headers/tStructures.h"

//
// tWall
//
class tWall
{
	public:

		// constructor()
		tWall( CGPoint position );

		// destructor()
		~tWall();

		// getPosition()
		CGPoint getPosition();

		// getLength()
		float getLength();

		// getWidth()
		float getWidth();

	private:

		CGPoint _position;
};

#endif