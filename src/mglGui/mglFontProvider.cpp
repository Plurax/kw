
#include "mglGui/mglFontProvider.h"
#include "mglDebug/mglDebug.h"
#include <sys/stat.h>

#include "boost/filesystem.hpp"


// constructor
mglFontProvider::mglFontProvider(void)
{
}

mglFontProvider::~mglFontProvider()  // destructor
{
	while(!m_VecFonts.empty()) { 
		delete m_VecFonts.back();
		m_VecFonts.pop_back();
	}
}

/**
 * Load all fonts listed below of the given XML element.
 * Each font tag should contain an absolute path to a font file.
 * @param _currentElement
 */
void mglFontProvider::loadFonts(json fontconfig)
{
	INIT_LOG("mglSystem", "loadFonts(DOMNode* _currentElement)");
	int fontsize = 0;

	for (auto& element : fontconfig["Fonts"])
	{
		LOG_TRACE("Adding font " << (element["file"]).get<string>());
		shared_ptr<mglValString> file = make_shared<mglValString>(((element["file"])).get<string>());
		int size = (element["size"]).get<int>();
		shared_ptr<mglValString> name = make_shared<mglValString>(((element["name"])).get<string>());
		AddFont(size, name, file);
	}
}

// this will add a font to the list
void mglFontProvider::AddFont(int _size, shared_ptr<mglValString> _name, shared_ptr<mglValString> _file)
{
	INIT_LOG("mglFontProvider", "AddFont(int _size, mglValString* _name, string* _AdvanceString, mglValString* _file)");
	LOG_TRACE("Loading Font " << *_name << " from File " << *_file);
	if (_name == NULL)
	{
		INIT_LOG("mglFontProvider", "AddTexFont(FTTexFont* fontobject)");
		THROW_TECHNICAL_EXCEPTION(1, "Error on loading Font (name)...\n");
	}

	if (_size == 0)
	{
		INIT_LOG("mglFontProvider", "AddTexFont(FTTexFont* fontobject)");
		THROW_TECHNICAL_EXCEPTION(2, "Error on loading Font (size)...\n");
	}

	if (_file == NULL)
	{
		INIT_LOG("mglFontProvider", "AddTexFont(FTTexFont* fontobject)");
		THROW_TECHNICAL_EXCEPTION(3, "Error on loading Font (file)...\n");
	}

	if (!boost::filesystem::exists(_file->str()->c_str()))
	{
		INIT_LOG("mglFontProvider", "AddTexFont(FTTexFont* fontobject)");
		THROW_TECHNICAL_EXCEPTION(4, "Fontfile " << *_file <<  " does not exist!\n");
	}

	FTFont* font = new FTTextureFont(_file->str()->c_str());

	font->FaceSize(_size); // Set the size initially - textures are loaded automatically by FTGL (SPEED!)
	font->CharMap(ft_encoding_unicode);
	m_VecFonts.push_back(font);
	m_MapFonts.insert(std::pair<mglValString, FTFont*>(*_name, font));
}


FTFont* mglFontProvider::GetFontByID(unsigned short index)
{
	if (m_VecFonts.empty())
		return NULL;

	if (m_VecFonts.size() < index)
		return NULL;
	else
		return m_VecFonts.at(index);
}

FTFont* mglFontProvider::GetFontByName(mglValString& _string)
{
	std::map<mglValString, FTFont*>::iterator fontIt;
	fontIt = m_MapFonts.find(_string);

	if (fontIt == m_MapFonts.end())
		return NULL;
	else
		return fontIt->second;
}

