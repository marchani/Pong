//
// tTexture2D.h
//

#ifndef ___TTEXTURE2D_H___
#define ___TTEXTURE2D_H___

#include "../../../Global Headers/tStructures.h"
#include "../../../Global Headers/tTexture.h"

//
// tTexture2D
//
class tTexture2D
{
	public:

		// constructor()
		tTexture2D( tTexture* texturePtr );

		// destructor()
		~tTexture2D();

		// getHeight()
		float getHeight() const;

		// getName()
		GLuint getName() const;

		// getTextureRatio()
		CGSize getTextureRatio() const;

		// getWidth()
		float getWidth() const;

	private:

		GLuint _name;	       // Holds the OpenGL name generated for this texture
		float  _width;
		float  _height;
		CGSize _textureRatio;  // The ratio between pixels and texels (texture coordinates).
};

#endif