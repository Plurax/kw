
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
	~mglFontProvider();  // destructor
	mglFontProvider* Inst();
	void Delete();

	void AddFont(FTPixmapFont* fontobject);
	FTPixmapFont* GetFontByID(unsigned short index);
private:
	mglFontProvider(); // private constructor (singleton class)
	static mglFontProvider* dInst;

	std::vector<FTPixmapFont*> PixMapFonts;
};


#endif
