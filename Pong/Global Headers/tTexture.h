//
// tTexture.h
//

#ifndef ___TTEXTURE_H___
#define ___TTEXTURE_H___

#include "tStructures.h"

struct tTexture
{
	GLubyte* imageData;  // Hold All The Color Values For The Image.
	GLuint bpp;          // Hold The Number Of Bits Per Pixel.           
	GLuint width;        // The Width Of The Entire Image.   
	GLuint height;       // The Height Of The Entire Image.  
	GLuint texID;        // Texture ID For Use With glBindTexture.   
	GLuint type;         // Data Stored In * ImageData (GL_RGB Or GL_RGBA)
};

#endif