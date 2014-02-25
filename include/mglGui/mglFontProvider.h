
#ifndef H_MGL_FONTPROVIDER
#define H_MGL_FONTPROVIDER


#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#include "mglValues/mglValString.h"


#include "FTGL/ftgl.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

using namespace xercesc;
using namespace std;

class mglFontProvider
{
public:	
	mglFontProvider(); // private constructor (singleton class)
	~mglFontProvider();  // destructor

    void loadFonts(DOMNode* currentElement);

	void AddFont(int _size, string* _name, string* _file);
	FTFont* GetFontByID(unsigned short index);
	FTFont* GetFontByName(string& _string);

private:
    void loadFont(DOMNode* currentElement);

    std::map<std::string, FTFont*> m_MapFonts;
	std::vector<FTFont*> m_VecFonts;
};


#endif
