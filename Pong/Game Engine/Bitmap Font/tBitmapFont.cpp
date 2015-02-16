//
// tBitmapFont.cpp
//

#include "tBitmapFont.h"

#include <assert.h>
#include <fstream>
#include <vector>
#include "../Image/tImage.h"

static const int kMaxCharsInFont = 223;

//
// constructor()
//
tBitmapFont::tBitmapFont( tImageRenderManager* imageRenderManagerPtr,
						  tTextureManager* textureManagerPtr,
						  const std::string& filename,
						  const std::string& controlFilename )
{
	assert( imageRenderManagerPtr != NULL );
	assert( textureManagerPtr != NULL );
	
	_imagePtr = new tImage( imageRenderManagerPtr, textureManagerPtr, filename, tTextureManager::kPNG );

	_charsArrayPtr = new std::vector< tBitmapFontChar* >();

	if( _charsArrayPtr != NULL )
	{
		_charsArrayPtr->resize( kMaxCharsInFont );

		for( unsigned int i = 0; i < _charsArrayPtr->size(); i++ )
		{
			_charsArrayPtr->at( i ) = new tBitmapFontChar();
			_charsArrayPtr->at( i )->imagePtr =
				new tImage( imageRenderManagerPtr, textureManagerPtr, filename, tTextureManager::kPNG );
		}
	}
	else // _charsArrayPtr == NULL
	{
		// Do nothing.
	}

	_lineHeight = 0.0f;

	// Parse the control file and populate _charsArrayPtr with the character definitions.
	parseFont( controlFilename );
}


//
// destructor()
//
tBitmapFont::~tBitmapFont()
{
	for( unsigned int i = 0; i < _charsArrayPtr->size(); i++)
	{
		delete _charsArrayPtr->at( i )->imagePtr;
		_charsArrayPtr->at( i )->imagePtr = NULL;

		delete _charsArrayPtr->at( i );
		_charsArrayPtr->at( i ) = NULL;
	}

	delete _charsArrayPtr;
	_charsArrayPtr = NULL;

	delete _imagePtr;
	_imagePtr = NULL;
}


//
// renderStringAt()
//
void tBitmapFont::renderStringAt( const CGPoint& point, const std::string& text )
{
	renderStringAt( point, Color4fMake( 1.0f, 1.0f, 1.0f, 0.0f ), text );

}


//
// renderStringAt()
//
void tBitmapFont::renderStringAt( CGPoint point, const Color4f& color, const std::string& text )
{
	assert( _imagePtr != NULL );
	assert( _charsArrayPtr != NULL );

	// Loop through all the characters in the text to be rendered
	unsigned int numCharsToRender = text.length();

	for( unsigned int i = 0; i < numCharsToRender; i++ )
	{
		// Grab the character value of the current character.  We take off 32 as the first
		// 32 characters of the fonts are not used.
		int charID = text[ i ] - 32;

		tBitmapFontChar* currentCharPtr = _charsArrayPtr->at( charID );
		assert( currentCharPtr != NULL );

		// Using the current x and y, calculate the correct position of the character
		// using the x and y offsets for each character.  This will cause the
		// characters to all sit on the line correctly with tails below the line.
		CGPoint renderPoint = CGPointMake( ( point.x + currentCharPtr->xOffset ),
			                               ( point.y + _lineHeight - ( currentCharPtr->height + currentCharPtr->yOffset ) ) );

		// Render the current character at the renderPoint.
		currentCharPtr->imagePtr->renderAtPoint( renderPoint, color, Scale2fMake( 0.95f, 0.95f ) );

		// Move x based on the amount to advance for the current character.
		point.x += currentCharPtr->xAdvance;
	}

	_imagePtr->setColor( color );
}


//
// parseFont()
//
void tBitmapFont::parseFont( const std::string& controlFilename )
{
	std::ifstream file( controlFilename );

	if( file.good() ==  true )
	{
		while( file.eof() != true )
		{
			// Read an entire line into memory.
			char buf[ 512 ];
			file.getline( buf, 512 );

			char* firstToken;
			char* nextToken;

			firstToken = strtok_s( buf, " ", &nextToken );

			if( ( firstToken != NULL ) && ( strcmp( firstToken, "common" ) == 0 ) )
			{
				parseCommon( nextToken );
			}
			else if( ( firstToken != NULL ) && ( strcmp( firstToken, "char" ) == 0 ) )
			{
				parseCharacterDefinition( nextToken );
			}
			else
			{
				// Do nothing.
			}
		}
	}
	else // file.good() !=  true
	{
		// Do nothing.
	}
}


//
// parseCommon()
//
void tBitmapFont::parseCommon( const std::string& line )
{
	char* lineChar = ( char* )line.c_str();
	char* nextToken;
	char* value;

	// Parse the 'lineHeight' token.
	char* currentToken = strtok_s( lineChar, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_lineHeight = ( float )atof( value );
}


//
// parseCharacterDefinition()
//
void tBitmapFont::parseCharacterDefinition( const std::string& line )
{
	assert( _imagePtr != NULL );
	assert( _charsArrayPtr != NULL );

	char* lineChar = ( char* )line.c_str();
	char* nextToken;
	char* value;

	// Parse the 'id' token.
	char* currentToken = strtok_s( lineChar, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	int charID = atoi( value ) - 32;

	// Parse the 'x' token.
	currentToken = strtok_s( NULL, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_charsArrayPtr->at( charID )->x = atoi( value );

	// Parse the 'y' token.
	currentToken = strtok_s( NULL, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_charsArrayPtr->at( charID )->y = atoi( value );

	// Parse the 'width' token.
	currentToken = strtok_s( NULL, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_charsArrayPtr->at( charID )->width = atoi( value );

	// Parse the 'height' token.
	currentToken = strtok_s( NULL, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_charsArrayPtr->at( charID )->height = ( float )atof( value );

	// Parse the 'xoffset' token.
	currentToken = strtok_s( NULL, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_charsArrayPtr->at( charID )->xOffset = ( float )atof( value );

	// Parse the 'yoffset' token.
	currentToken = strtok_s( NULL, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_charsArrayPtr->at( charID )->yOffset = ( float )atof( value );

	// Parse the 'xadvance' token.
	currentToken = strtok_s( NULL, " ", &nextToken );
	strtok_s( currentToken, "=", &value );
	_charsArrayPtr->at( charID )->xAdvance = atoi( value );

	_charsArrayPtr->at( charID )->imagePtr->setSubtexture( CGRectMake( ( float )_charsArrayPtr->at( charID )->x,
                                                                       ( float )_charsArrayPtr->at( charID )->y,
						     	                                       ( float )_charsArrayPtr->at( charID )->width,
							                                           ( float )_charsArrayPtr->at( charID )->height ) );
}