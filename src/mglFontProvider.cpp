
#include "mglGui/mglFontProvider.h"
#include "mglDebug/mglDebug.h"


// constructor
mglFontProvider::mglFontProvider(void)
{
}

mglFontProvider::~mglFontProvider()  // destructor
{
	while(!m_PixMapFonts.empty()) delete m_PixMapFonts.back(), m_PixMapFonts.pop_back();

}


// this will add a font to the list
void mglFontProvider::AddPixMapFont(FTPixmapFont* fontobject)
{
	if (fontobject != NULL)
	{
		m_PixMapFonts.push_back(fontobject);
	}
	else
	{
		INIT_LOG("mglFontProvider", "AddPixMapFont(FTPicmapFont* fontobject)");
		THROW_TECHNICAL_EXCEPTION(1, "Error on loading Font...\n");
	}
}


FTPixmapFont* mglFontProvider::GetPixMapFontByID(unsigned short index)
{
	return m_PixMapFonts.at(index);
}
