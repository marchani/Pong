//
// tTGAFileReader.cpp
//

#include "tTGAFileReader.h"

#include <io.h>
#include <sys/stat.h>
#include "../../../Global Headers/tTexture.h"

//
// Constructor()
//
tTGAFileReader::tTGAFileReader()
{
}


//
// Destructor()
//
tTGAFileReader::~tTGAFileReader()
{
}


//
// loadFile()
//
bool tTGAFileReader::loadFile( tTexture* texturePtr, const char* filename )
{
	FILE* filePtr;
	errno_t error = fopen_s( &filePtr, filename, "rb" );

	if( filePtr == NULL )
	{
	    return false;
	}

	tTGAHeader tgaHeaderInformation;

	if( fread( &tgaHeaderInformation, sizeof( tTGAHeader ), 1, filePtr ) == 0 )
	{
	    return false;
	}

	// TGA Header for an uncompressed TGA file.
	GLubyte uTGAcompare[ 12 ] = { 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	if( memcmp( uTGAcompare, &tgaHeaderInformation, sizeof( tgaHeaderInformation ) ) == 0 )
	{
	    loadUncompressedFile( texturePtr, filename, filePtr );
	}
	else
	{
	    return false;
	}

	return true;
}


//
// loadUncompressedFile()
//
bool tTGAFileReader::loadUncompressedFile( tTexture* texturePtr, const char* filename, FILE* filePtr )
{
	tTGA tga;

	if( fread( tga.header, sizeof( tga.header ), 1, filePtr ) == 0 )
	{                                       
	    return false;
	}

	texturePtr->width  = tga.header[1] * 256 + tga.header[0];
	texturePtr->height = tga.header[3] * 256 + tga.header[2];
	texturePtr->bpp = tga.header[4];
	tga.Width = texturePtr->width;
	tga.Height = texturePtr->height;
	tga.Bpp = texturePtr->bpp;

	// Make Sure All Information Is Valid
	if( ( texturePtr->width <= 0 ) ||
		( texturePtr->height <= 0 ) ||
		( ( texturePtr->bpp != 24 ) && ( texturePtr->bpp != 32 ) ) )
	{
	    return false;
	}

	if( texturePtr->bpp == 24 )
	{
		texturePtr->type = GL_RGB;
	}
	else
	{
		texturePtr->type = GL_RGBA;
	}

	tga.bytesPerPixel = ( tga.Bpp / 8 );
	
	// Calculate Memory Needed To Store Image
	tga.imageSize = ( tga.bytesPerPixel * tga.Width * tga.Height );

	// Allocate Memory
	texturePtr->imageData = new GLubyte[ tga.imageSize ];
	if( texturePtr->imageData == NULL )
	{
	    return false;
	}

	// Attempt To Read All The Image Data
	size_t numBytesRead = fread_s( texturePtr->imageData, tga.imageSize, sizeof( GLubyte ), tga.imageSize, filePtr );
	if( numBytesRead != tga.imageSize )
	{
		return false;
	}

	// Start The Loop
	for( GLuint cswap = 0; cswap < ( int )tga.imageSize; cswap += tga.bytesPerPixel )
    {
        // 1st Byte XOR 3rd Byte XOR 1st Byte XOR 3rd Byte
        texturePtr->imageData[cswap] ^= texturePtr->imageData[cswap+2] ^=
        texturePtr->imageData[cswap] ^= texturePtr->imageData[cswap+2];
    }

    fclose( filePtr );
    return true;
}