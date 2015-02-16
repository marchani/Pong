//
// tStructures.h
//

#ifndef ___TSTRUCTURES_H___
#define ___TSTRUCTURES_H___

#pragma comment(lib, "OpenGL32.lib")
#include <windows.h>
#include <gl\gl.h>

//
// Color4f
//
struct Color4f
{
	float red;
	float green;
	float blue;
	float alpha;
};


//
// Scale2f
//
struct Scale2f
{
	float x;
	float y;
};


//
// CGPoint
//
struct CGPoint
{
	float x;
	float y;
};


//
// CGSize
//
struct CGSize
{
	float width;
	float height;
};


//
// CGRect
//
struct CGRect
{
   float x;
   float y;
   float width;
   float height;
};


//
// Color4fMake()
//
static inline Color4f Color4fMake( float red, float green, float blue, float alpha )
{
	Color4f color;
	color.red = red;
	color.green = green;
	color.blue = blue;
	color.alpha = alpha;

	return color;
}


//
// Scale2Make()
//
static inline Scale2f Scale2fMake( float x, float y )
{
	Scale2f scale;
	scale.x = x;
	scale.y = y;

	return scale;
}


//
// CGPointMake()
//
static inline CGPoint CGPointMake( float x, float y )
{
	CGPoint point;
	point.x = x;
	point.y = y;

	return point;
}


//
// CGSizeMake()
//
static inline CGSize CGSizeMake( float width, float height )
{
	CGSize size;
	size.width = width;
	size.height = height;

	return size;
}


//
// CGRectMake()
//
static inline CGRect CGRectMake( float x, float y, float width, float height )
{
	CGRect rect;
	rect.x = x;
	rect.y = y;
	rect.width = width;
	rect.height = height;

	return rect;
}

#endif