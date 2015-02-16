//
// tSpriteSheet.cpp
//

#include "tSpriteSheet.h"

#include "../Image/tImage.h"

//
// constructor()
//
tSpriteSheet::tSpriteSheet( tImageRenderManager* imageRenderManagerPtr,
				  		    tTextureManager* textureManagerPtr,
						    const std::string& filename,
						    const tTextureManager::kImageFileFormat& imageFileFormat )
{
	_imagePtr = new tImage( imageRenderManagerPtr, textureManagerPtr, filename, imageFileFormat );
}


//
// destructor()
//
tSpriteSheet::~tSpriteSheet()
{
	delete _imagePtr;
	_imagePtr = NULL;
}


//
// spriteImageAtCoords()
//
tImage* tSpriteSheet::spriteImageAtCoords( const CGPoint& point )
{
	return _imagePtr;
}
