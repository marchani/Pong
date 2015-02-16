//
// tTextureManager.h
//

#ifndef ___TTEXTUREMANAGER_H___
#define ___TTEXTUREMANAGER_H___

#include <map>
#include <string>

class tTexture2D;

//
// tTextureManager
//
class tTextureManager
{
	public:

		enum kImageFileFormat
		{
			kPNG = 0,
			kTGA = 1
		};

	public:

		// constructor()
		tTextureManager();

		// destructor()
		~tTextureManager();

		// textureWithFileName()
		tTexture2D* textureWithFilename( const std::string& filename, const kImageFileFormat& imageFileFormat );

	private:

		// init()
		void init();

	private:

		std::map< std::string, tTexture2D* >* cachedTextures;  // A dictionary of all textures that are currently in use
};

#endif