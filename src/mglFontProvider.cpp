
#include "mglGui/mglFontProvider.h"
#include "mglDebug/mglDebug.h"


// constructor
mglFontProvider::mglFontProvider(void)
{
}

mglFontProvider::~mglFontProvider()  // destructor
{
	while(!m_MapFonts.empty()) delete m_MapFonts.back(), m_MapFonts.pop_back();

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
				string* name = new string(XMLString::transcode(currentElement->getTextContent()));
				LOG_TRACE("Got Font from file: " << (*name));
				AddFont(name->c_str());
			}
		}
	}

	XMLString::release(&TAG_Font);

}
// this will add a font to the list
void mglFontProvider::AddFont(const char* fontobject)
{
	bool err = false;
	if (fontobject != NULL)
	{
		FTFont* font = new FTTextureFont(fontobject);

		m_MapFonts.push_back(font);
	}
	else
		err = true;

	if (err)
	{
		INIT_LOG("mglFontProvider", "AddTexFont(FTTexFont* fontobject)");
		THROW_TECHNICAL_EXCEPTION(1, "Error on loading Font...\n");
	}
}


FTFont* mglFontProvider::GetFontByID(unsigned short index)
{
	return m_MapFonts.at(index);
}

