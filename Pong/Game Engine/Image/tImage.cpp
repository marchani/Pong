//
// tImage.cpp
//

#include "tImage.h"

#include <assert.h>
#include "../Managers/Image Render Manager/tImageRenderManager.h"
#include "../Managers/Texture Manager/tTextureManager.h"
#include "Texture2D/tTexture2D.h"

//
// constructor()
//
tImage::tImage( tImageRenderManager* imageRenderManagerPtr,
			    tTextureManager* textureManagerPtr,
				const std::string& filename,
				const tTextureManager::kImageFileFormat& imageFileFormat )
{
	assert( imageRenderManagerPtr != NULL );
	assert( textureManagerPtr != NULL );

	_imageRenderManagerPtr = imageRenderManagerPtr;
	_textureManagerPtr = textureManagerPtr;

	_filename = filename;
	_imageFileFormat = imageFileFormat;
	_color = Color4fMake( 1.0f, 1.0f, 1.0f, 0.0f );
	_scale = Scale2fMake( 1.0f, 1.0f );
	_flipVertical = false;
	_point = CGPointMake( 0.0f, 0.0f );

	_texturePtr = _textureManagerPtr->textureWithFilename( filename, imageFileFormat );
	_textureName = _texturePtr->getName();
	_textureSize = CGSizeMake( 1.0f, 1.0f );
	_textureRatio = CGSizeMake( _texturePtr->getTextureRatio().width, _texturePtr->getTextureRatio().height );
	_textureOffset = CGPointMake( 0.0f, 0.0f );

	_imageSize = CGSizeMake( _texturePtr->getWidth(), _texturePtr->getHeight() );
}


//
// setSubtexture()
//
void tImage::setSubtexture( CGRect subTexture )
{
	_textureOffset.x = _textureRatio.width * subTexture.x;
    _textureOffset.y = _textureRatio.height * subTexture.y;

	_imageSize = CGSizeMake( subTexture.width, subTexture.height );
       
    // Calculate the width and height of the sub region this image is going to use.
	_textureSize.width = ( _textureRatio.width * subTexture.width );
    _textureSize.height = ( _textureRatio.height * subTexture.height );
}


//
// destructor()
//
tImage::~tImage()
{
}


//
// getColor()
//
Color4f tImage::getColor() const
{
	return _color;
}


//
// setColor()
//
void tImage::setColor( const Color4f& color )
{
	_color = color;
}


//
// getFlipVertical()
//
bool tImage::getFlipVertical() const
{
	return _flipVertical;
}


//
// setFlipVertical()
//
void tImage::setFlipVertical( bool flipVertical )
{
	_flipVertical = flipVertical;
}


//
// getImageSize()
//
CGSize tImage::getImageSize() const
{
	return _imageSize;
}


//
// getPoint()
//
CGPoint tImage::getPoint() const
{
	return _point;
}


//
// getScale()
//
Scale2f tImage::getScale() const
{
	return _scale;
}


//
// setScale()
//
void tImage::setScale( Scale2f scale )
{
	_imageSize.width = _imageSize.width * scale.x;
	_imageSize.height = _imageSize.height * scale.y;

	_scale = scale;
}


//
// getTextureName()
//
GLuint tImage::getTextureName() const
{
	return _textureName;
}



//
// getTextureOffset()
//
CGPoint tImage::getTextureOffset() const
{
	return _textureOffset;
}


//
// getTextureSize()
//
CGSize tImage::getTextureSize() const
{
	return _textureSize;
}


//
// renderAtPoint()
//
void tImage::renderAtPoint( const CGPoint& point, const Color4f& color, const Scale2f& scale )
{
	_point = point;
	_color = color;
	_scale = scale;

	render();
}


//
// renderCenteredAtPoint()
//
void tImage::renderCenteredAtPoint( const CGPoint& point, const Scale2f& scale )
{
	CGPoint centerPoint = CGPointMake( point.x - ( ( _imageSize.width * scale.x ) / 2 ),
		                               point.y - ( ( _imageSize.height * scale.y ) / 2 ) );

	renderAtPoint( centerPoint, _color, scale );
}


//
// render()
//
void tImage::render()
{
	if( _imageRenderManagerPtr != NULL )
	{
		// Add this image to the render queue.  This will cause this image to be
		// rendered the next time the renderManager is asked to render.
		_imageRenderManagerPtr->addImageToRenderQueue( this );
	}
	else // _imageRenderManagerPtr == NULL
	{
		// Do nothing.
	}
}