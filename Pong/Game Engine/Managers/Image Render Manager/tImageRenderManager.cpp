//
// tImageRenderManager.cpp
//

#include "tImageRenderManager.h"

#include <assert.h>
#include "../../Image/tImage.h"

//
// constructor()
//
tImageRenderManager::tImageRenderManager()
{
	for( int i = 0; i < kMaxTextures; i++ )
	{
		_texturesToRender[ i ] = 0;
	}

	_renderTextureCount = 0;

	_imagesToRender.clear();
	_locationsOfImagesToRender.clear();
	_colorOfImagesToRender.clear();
	_scaleOfImagesToRender.clear();
	_flipVerticalImagesToRender.clear();

}


//
// destructor()
//
tImageRenderManager::~tImageRenderManager()
{
}


//
// addImageToRenderQueue()
//
void tImageRenderManager::addImageToRenderQueue( tImage* imagePtr )
{
	assert( imagePtr != NULL );

	// Add a pointer to the image to the ImagesToRender vector.
	_imagesToRender.push_back( imagePtr );

	_locationsOfImagesToRender.push_back( imagePtr->getPoint() );
	_colorOfImagesToRender.push_back( imagePtr->getColor() );
	_scaleOfImagesToRender.push_back( imagePtr->getScale() );
	_flipVerticalImagesToRender.push_back( imagePtr->getFlipVertical() );

	// Add the texture used for this image to the list of textures to be rendered
	addToTextureList( imagePtr->getTextureName() );
}


//
// renderImages()
//
void tImageRenderManager::renderImages()
{	
    // Loop through the texture index array rendering the images as necessary
	int size = _imagesToRender.size();

	for( int textureIndex = 0; textureIndex < size; textureIndex++ ) 
	{
		tImage* imagePtr = _imagesToRender.at( textureIndex );
		assert( imagePtr != NULL );

		float x1 = _locationsOfImagesToRender.at( textureIndex ).x;
		float y1 = _locationsOfImagesToRender.at( textureIndex ).y;
		float width = imagePtr->getImageSize().width * _scaleOfImagesToRender.at( textureIndex ).x;
		float height = imagePtr->getImageSize().height * _scaleOfImagesToRender.at( textureIndex ).y;

		float textureX1 = imagePtr->getTextureOffset().x;
		float textureY1 = imagePtr->getTextureOffset().y;
		float textureX2 = imagePtr->getTextureOffset().x + imagePtr->getTextureSize().width;
		float textureY2 = imagePtr->getTextureOffset().y + imagePtr->getTextureSize().height;

		Color4f color = _colorOfImagesToRender.at( textureIndex );
		glColor4f( color.red, color.green, color.blue, color.alpha );

		if( _flipVerticalImagesToRender.at( textureIndex ) == true )
		{
			float temp = textureY1;
			textureY1 = textureY2;
			textureY2 = temp;
		}
		else // _flipVerticalImagesToRender.at( textureIndex == false )
		{
			// Do nothing.
		}

		int textureID = imagePtr->getTextureName();

        // Bind to the textureName of the current texture.  This is the key of the texture
        // structure
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBindTexture( GL_TEXTURE_2D, textureID );
		glBegin( GL_TRIANGLE_STRIP );
		glTexCoord2d( textureX1, textureY2 ); glVertex2f( x1, y1 );
		glTexCoord2d( textureX2, textureY2 ); glVertex2f( x1 + width, y1 );
		glTexCoord2d( textureX1, textureY1 ); glVertex2f( x1, y1 + height );
		glTexCoord2d( textureX2, textureY1 ); glVertex2f( x1 + width, y1 + height );
		glEnd();
    }
    
    // Reset the number of textures which need to be rendered
    _renderTextureCount = 0;
	_imagesToRender.clear();
	_locationsOfImagesToRender.clear();
	_colorOfImagesToRender.clear();
	_scaleOfImagesToRender.clear();
	_flipVerticalImagesToRender.clear();
}


//
// addToTextureList()
//
void tImageRenderManager::addToTextureList( unsigned int textureName )
{
	// Check to see if the texture for this image has already been added to the queue
    BOOL textureFound = false;

    for( int index = 0; index < _renderTextureCount; index++ )
	{
		if( _texturesToRender[ index ] == textureName )
		{
            textureFound = true;
            break;
        }
		else
		{
			// Do nothing.
		}
    }
    
	if( textureFound == false )
	{
        // This is the first time this texture has been placed on the queue, so
		// add this texture to the texturesToRender array.
        _texturesToRender[ _renderTextureCount++ ] = textureName;
	}
	else // textureFound == true
	{
		// Do nothing.
	}
}