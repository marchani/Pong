//
// tSpriteSheet.h
//

#ifndef ___TSPRITESHEET_H___
#define ___TSPRITESHEET_H___

#include <string>
#include "../../Global Headers/tStructures.h"
#include "../Managers/Texture Manager/tTextureManager.h"

class tImage;
class tImageRenderManager;
class tTextureManager;

//
// tSpriteSheet
//
class tSpriteSheet
{
	public:

		// constructor()
		tSpriteSheet( tImageRenderManager* imageRenderManagerPtr,
			          tTextureManager* textureManagerPtr,
					  const std::string& filename,
					  const tTextureManager::kImageFileFormat& imageFileFormat );

		// destructor()
		~tSpriteSheet();

		// spriteImageAtCoords()
		tImage* spriteImageAtCoords( const CGPoint& aPoint );

	private:

		tImage* _imagePtr;  // Image which is being used for this spritesheet.

};

#endif