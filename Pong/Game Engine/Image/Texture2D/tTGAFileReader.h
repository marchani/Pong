//
// tTGAFileReader.h
//

#ifndef ___TTGAFILEREADER_H___
#define ___TTGAFILEREADER_H___

#pragma comment(lib, "OpenGL32.lib")
#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>

struct tTexture;

//
// tTGAFileReader
//
class tTGAFileReader
{
	public:

		// constructor
		tTGAFileReader();

		// destructor
		~tTGAFileReader();

		// loadFile()
		bool loadFile( tTexture* texturePtr, const char* filename );

	private:

		struct tTGAHeader
		{
			GLubyte Header[ 12 ];  // File Header To Determine File Type
		};

		struct tTGA
		{
			GLubyte header[ 6 ];    // Holds The First 6 Useful Bytes Of The File
			GLuint  bytesPerPixel;  // Number Of BYTES Per Pixel (3 Or 4)
			GLuint  imageSize;      // Amount Of Memory Needed To Hold The Image
			GLuint  type;           // The Type Of Image, GL_RGB Or GL_RGBA
			GLuint  Height;         // Height Of Image                  
			GLuint  Width;          // Width Of Image               
			GLuint  Bpp;            // Number Of BITS Per Pixel (24 Or 32)
		};

	private:

		// loadUncompressedFile()
		bool loadUncompressedFile( tTexture* texturePtr, const char* filename, FILE* filePtr );

};

#endif