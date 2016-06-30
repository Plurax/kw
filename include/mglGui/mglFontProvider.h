/*
 * mglFontProvider.h
 *
 *  Created on: 21.03.2014
 *      Author: cromas
 */


#ifndef H_MGL_FONTPROVIDER
#define H_MGL_FONTPROVIDER

#ifdef WIN32
#include "Windows.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#endif

#include <stdio.h>
#include <vector>
#include <map>

#include "mglValues/mglValString.h"


#include "FTGL/ftgl.h"

#include <json.hpp>

using namespace std;
using json = nlohmann::json;

class mglFontProvider
{
public:	
	mglFontProvider(); // private constructor (singleton class)
	~mglFontProvider();  // destructor

    void loadFonts(json fontconfig);

    void AddFont(int _size, shared_ptr<mglValString> _name, shared_ptr<mglValString> _file);
	FTFont* GetFontByID(unsigned short index);
	FTFont* GetFontByName(mglValString& _string);

private:
    std::map<mglValString, FTFont*> m_MapFonts;
	std::vector<FTFont*> m_VecFonts;
};


#endif
