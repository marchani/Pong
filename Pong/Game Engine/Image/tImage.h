//
// tImage.h
//

#ifndef ___TIMAGE_H___
#define ___TIMAGE_H___

#include <string>
#include "../../Global Headers/tStructures.h"
#include "../Managers/Texture Manager/tTextureManager.h"

class tImageRenderManager;
class tTexture2D;

//
// tImage
//
class tImage
{
	public:

		// constructor()
		tImage( tImageRenderManager* imageRenderManagerPtr,
			    tTextureManager* textureManagerPtr,
				const std::string& filename,
				const tTextureManager::kImageFileFormat& imageFileFormat );

		// destructor()
		~tImage();

		// getColor()
		Color4f getColor() const;

		// setColor()
		void setColor( const Color4f& color );

		// getFlipVertical()
		bool getFlipVertical() const;
		
		// setFlipVertical()
		void setFlipVertical( bool flipVertical );

		// getImageSize()
		CGSize getImageSize() const;

		// getPoint()
		CGPoint getPoint() const;

		// getScale()
		Scale2f getScale() const;

		// setScale()
		void setScale( Scale2f scale );

		// getTextureName()
		GLuint getTextureName() const;

		// getTextureOffset()
		CGPoint getTextureOffset() const;

		// getTextureSize()
		CGSize getTextureSize() const;

		// setSubtexture()
		void setSubtexture( CGRect subTexture );

		// renderAtPoint()
		void renderAtPoint( const CGPoint& point, const Color4f& color, const Scale2f& scale );

		// renderCenteredAtPoint()
		void renderCenteredAtPoint( const CGPoint& point, const Scale2f& scale );

	private:

		// render()
		void render();

	private:

		tImageRenderManager* _imageRenderManagerPtr;
		tTextureManager*    _textureManagerPtr;

		std::string _filename;
		tTextureManager::kImageFileFormat _imageFileFormat;
		CGSize _imageSize;	                                 // Width and height of the image within the texture this instance represents.
		Color4f _color;
		Scale2f _scale;
		bool _flipVertical;
		CGPoint _point;                                      // Point at which the image will be rendered.

		tTexture2D* _texturePtr;  // Texture2D object which has been created with the image provided to create this
		GLuint _textureName;	  // Name of the OpenGL texture used by the associated Texture2D object
		CGSize _textureSize;	  // Width and height of the texture this image is actually using
		CGSize _textureRatio;
		CGPoint _textureOffset;
};

#endif