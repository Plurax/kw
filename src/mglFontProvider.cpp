
#include "mglGui/mglFontProvider.h"
#include "mglLogger/mglLogger.h"


mglFontProvider* mglFontProvider::dInst = NULL;

// constructor
mglFontProvider::mglFontProvider(void)
{
}

mglFontProvider::~mglFontProvider()  // destructor
{
	while(!PixMapFonts.empty()) delete PixMapFonts.back(), PixMapFonts.pop_back();

}

// singleton implementation
mglFontProvider* mglFontProvider::Inst()
{
	if (dInst == 0)
		dInst = new mglFontProvider();
	
	return dInst;
}

// this will add a font to the list
void mglFontProvider::AddFont(FTPixmapFont* fontobject)
{
	if (fontobject != NULL)
	{
		PixMapFonts.push_back(fontobject);
	}
	else
	{
		//Logger << ("Error on loading Font...\n");
	}
}


void mglFontProvider::Delete()
{
	if (dInst)
		delete dInst;
}

FTPixmapFont* mglFontProvider::GetFontByID(unsigned short index)
{
	return PixMapFonts.at(index);
}
