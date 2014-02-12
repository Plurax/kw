
#ifndef H_MGL_FONTPROVIDER
#define H_MGL_FONTPROVIDER


#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#include <stdio.h>
#include <vector>
#include <string>


#include "FTGL/ftgl.h"

class mglFontProvider
{
public:	
	mglFontProvider(); // private constructor (singleton class)
	~mglFontProvider();  // destructor

	void AddPixMapFont(FTPixmapFont* fontobject);
	FTPixmapFont* GetPixMapFontByID(unsigned short index);

	void AddTexFont(FTTextureFont* fontobject);
	FTTextureFont* GetTexFontByID(unsigned short index);

private:
	std::vector<FTPixmapFont*> m_PixMapFonts;
	std::vector<FTTextureFont*> m_TextureFonts;
};


#endif
