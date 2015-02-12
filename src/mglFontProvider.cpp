
#include "mglGui/mglFontProvider.h"
#include "mglDebug/mglDebug.h"
#include <sys/stat.h>

// constructor
mglFontProvider::mglFontProvider(void)
{
}

mglFontProvider::~mglFontProvider()  // destructor
{
	while(!m_VecFonts.empty()) delete m_VecFonts.back(), m_VecFonts.pop_back();
}


/**
 * Load all fonts listed below of the given XML element.
 * Each font tag should contain an absolute path to a font file.
 * @param _currentElement
 */
void mglFontProvider::loadFonts(DOMNode* _currentElement)
{
	INIT_LOG("mglSystem", "loadFonts(DOMNode* _currentElement)");

	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >(_currentElement);

	DOMNodeList*      children = currentElement->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_Font = XMLString::transcode("Font");

	// For all nodes, children of "GUI" in the XML tree.
	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{

			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
			if ( XMLString::equals(currentElement->getTagName(), TAG_Font))
			{
				loadFont(currentElement);
			}
		}
	}

	XMLString::release(&TAG_Font);

}

/**
 * Load all fonts listed below of the given XML element.
 * Each font tag should contain an absolute path to a font file.
 * @param _currentElement
 */
void mglFontProvider::loadFont(DOMNode* _currentElement)
{
	INIT_LOG("mglSystem", "loadFonts(DOMNode* _currentElement)");

	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >(_currentElement);

	DOMNodeList*      children = currentElement->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_FontFile = XMLString::transcode("file");
	XMLCh* TAG_FontSize = XMLString::transcode("size");
	XMLCh* TAG_FontName = XMLString::transcode("name");

	int fontsize = 0;
	mglValString* file_str = NULL;
	mglValString* name_str = NULL;
	string* size_str = NULL;
	string* advance_str = NULL;

	// For all nodes, children of "GUI" in the XML tree.
	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{

			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
			if ( XMLString::equals(currentElement->getTagName(), TAG_FontFile))
			{
				file_str = new mglValString(XMLString::transcode(currentElement->getTextContent()));
				LOG_TRACE("Got Font from file: " << (*file_str));
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_FontSize))
			{
				size_str = new string(XMLString::transcode(currentElement->getTextContent()));
				fontsize = atoi(size_str->c_str());;
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_FontName))
			{
				name_str = new mglValString(XMLString::transcode(currentElement->getTextContent()));
			}

		}
	}

	AddFont(fontsize, name_str, file_str);

	delete name_str;
	delete file_str;
	delete size_str;

	XMLString::release(&TAG_FontFile);
	XMLString::release(&TAG_FontName);
	XMLString::release(&TAG_FontSize);
}

// this will add a font to the list
void mglFontProvider::AddFont(int _size, mglValString* _name, mglValString* _file)
{
	INIT_LOG("mglFontProvider", "AddFont(int _size, mglValString* _name, string* _AdvanceString, mglValString* _file)");

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

/*	struct stat buffer;
	if  (stat (_file->str()->c_str(), &buffer) == 0);
	{
		INIT_LOG("mglFontProvider", "AddTexFont(FTTexFont* fontobject)");
		THROW_TECHNICAL_EXCEPTION(4, "Fontfile " << *_file <<  " does not exist!\n");
	}
*/
	FTFont* font = new FTTextureFont(_file->str()->c_str());

	font->FaceSize(_size); // Set the size initially - textures are loaded automatically by FTGL (SPEED!)
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

