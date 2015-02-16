//
// tTextureManager.cpp
//

#include "tTextureManager.h"

#include <iostream>
#include <vector>
#include "../../Image/Texture2D/lodepng.h"
#include "../../Image/Texture2D/tTexture2D.h"
#include "../../Image/Texture2D/tTGAFileReader.h"

//
// constructor()
//
tTextureManager::tTextureManager()
{
	cachedTextures = new std::map< std::string, tTexture2D* >();
}


//
// destructor()
//
tTextureManager::~tTextureManager()
{
	delete cachedTextures;
	cachedTextures = NULL;
}


//
// textureWithFileName()
//
tTexture2D* tTextureManager::textureWithFilename( const std::string& filename, const kImageFileFormat& imageFileFormat )
{
    // Try to get a texture from cachedTextures with the supplied key.
	std::map< std::string, tTexture2D* >::iterator it = cachedTextures->find( filename );

	if( it != cachedTextures->end() )
	{
		return it->second;
	}

	bool format = true;

	tTexture texture;

	switch( imageFileFormat )
	{
		case tTextureManager::kImageFileFormat::kPNG:
		{
			std::vector< unsigned char > image;
			unsigned int width = 0;
			unsigned int height = 0;

			unsigned error = lodepng::decode( image, width, height, filename );

			if( error ) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

			texture.bpp = 32;
			texture.type = GL_RGBA;
			texture.width = width;
			texture.height = height;

			int size = image.size();
			GLubyte* im = new GLubyte[ size ];

			for( int i = 0; i < size; i++ )
			{
				im[ i ] = image.at( i );
			}

			texture.imageData = im;

			break;
		}
		case tTextureManager::kImageFileFormat::kTGA:
		{
			// Load the texture for the title screen.
			tTGAFileReader fileReader;
			fileReader.loadFile( &texture, filename.c_str() );

			break;
		}
		default:
		{
			// Do nothing.
		}
	}

	tTexture2D* cachedTexture = new tTexture2D( &texture );

	cachedTextures->insert( std::pair< std::string, tTexture2D* >( filename, cachedTexture ) );
		
	// Return the texture which is autoreleased as the caller is responsible for it
    return cachedTexture;
}