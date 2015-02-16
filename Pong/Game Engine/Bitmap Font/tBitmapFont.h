//
// tBitmapFont.h
//

#ifndef ___BITMAPFONT_H___
#define ___BITMAPFONT_H___

#pragma comment(lib, "OpenGL32.lib")
#include <windows.h>
#include <stdio.h>
#include <gl\gl.h>
#include <string>
#include <vector>
#include "../../Global Headers/tStructures.h"
#include "../Managers/Texture Manager/tTextureManager.h"

class tImage;
class tImageRenderManager;

//
// tBitmapFont
//
class tBitmapFont
{
	public:

		// constructor()
		tBitmapFont( tImageRenderManager* imageRenderManagerPtr,
			         tTextureManager* textureManagerPtr,
					 const std::string& filename,
					 const std::string& controlFilename );

		// destructor()
		~tBitmapFont();

		// renderStringAt()
		//
		// This is a convenience function to renderStringAt() so the user does not have to pass a color.
		//
		void renderStringAt( const CGPoint& point, const std::string& text );

		// renderStringAt()
		void renderStringAt( CGPoint point, const Color4f& color, const std::string& text );

	private:

		typedef struct tBitmapFontChar
		{
			int charID;
			int x;
			int y;
			int width;
			float height;
			float xOffset;
			float yOffset;
			int xAdvance;
			tImage* imagePtr;
			float scale;
		};

	private:

		// parseFont()
		void parseFont( const std::string& controlFilename );

		// parseCommon()
		void parseCommon( const std::string& line );

		// parseCharacterDefinition()
		void parseCharacterDefinition( const std::string& line );

	private:

		tImage* _imagePtr;

		std::vector< tBitmapFontChar* >* _charsArrayPtr;

		float _lineHeight;
		
};

#endif