//
// tTexture2D.cpp
//

#include "tTexture2D.h"

//
// constructor()
//
tTexture2D::tTexture2D( tTexture* texturePtr )
{
	glGenTextures( 1, &_name );
	glBindTexture( GL_TEXTURE_2D, _name );
	glTexImage2D( GL_TEXTURE_2D, 0, texturePtr->bpp / 8, texturePtr->width, texturePtr->height, 0, texturePtr->type, GL_UNSIGNED_BYTE, texturePtr->imageData );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	_width = ( float )texturePtr->width;
	_height = ( float )texturePtr->height;

	// So that we can convert pixels into texture coordinates easily we need to
	// calculate the pixel-to-texture ratio for this texture.  Remember that the
	// maximum s, t texture coordinates you can have are 1.0, 1.0f.  Behavior if
	// the texture coordinates are greater than 1.0f will be based on the clamping
	// and wrapping configuration for this texture.
	_textureRatio = CGSizeMake( 1.0f / _width, 1.0f / _height );
}


//
// destructor()
//
tTexture2D::~tTexture2D()
{
}


//
// getHeight()
//
float tTexture2D::getHeight() const
{
	return _height;
}


//
// getName()
//
GLuint tTexture2D::getName() const
{
	return _name;
}


//
// getTextureRatio()
//
CGSize tTexture2D::getTextureRatio() const
{
	return _textureRatio;
}


//
// getWidth()
//
float tTexture2D::getWidth() const
{
	return _width;
}