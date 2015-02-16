//
// tImageRenderManager.h
//

#ifndef ___TIMAGERENDERMANAGER_H___
#define ___TIMAGERENDERMANAGER_H___

#include <vector>
#include "../../../Global Headers/tStructures.h"

class tImage;

static const int kMaxTextures = 20;

//
// tImageRenderManager
//
class tImageRenderManager
{
	public:

		// constructor()
		tImageRenderManager();

		// destructor()
		~tImageRenderManager();

		// addImageToRenderQueue()
		void addImageToRenderQueue( tImage* imagePtr );

		// renderImages()
		void renderImages();

	private:

		// addToTextureList()
		void addToTextureList( unsigned int textureName );

	private:

		int _texturesToRender[ kMaxTextures ];  // Array to store a list of the textures which need to be rendered.  Each time an image
											    // is added to the render queue with a texture which has not been added to the queue before
											    // the new texture name is added to this array.  This array then drives the textures which
											    // are processed during a render.

		int _renderTextureCount;			    // Number of textures to render.

		std::vector< tImage* >  _imagesToRender;
		std::vector< CGPoint > _locationsOfImagesToRender;
		std::vector< Color4f > _colorOfImagesToRender;
		std::vector< Scale2f > _scaleOfImagesToRender;
		std::vector< bool >    _flipVerticalImagesToRender;

};

#endif
