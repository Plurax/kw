/*
 * mglAppConfiguration.cpp
 *
 *  Created on: 19.01.2014
 *      Author: cromas
 */

#include "mglAppConfiguration.h"

void mglAppConfiguration::init(DOMNode* appconfig)
{
	DOMNodeList*      children = appconfig->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_GL = XMLString::transcode("GL");
	XMLCh* TAG_yres = XMLString::transcode("yres");
	XMLCh* TAG_xres = XMLString::transcode("xres");

	unsigned int uisReadVal = 0;
	char* valTagText;

	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );

			if ( XMLString::equals(currentElement->getTagName(), TAG_GL))
			{
				DOMNodeList* channel_children = currentElement->getChildNodes();
				for( XMLSize_t ccxx = 0; ccxx < channel_children->getLength(); ++ccxx )
				{
					DOMNode* channel_child= channel_children->item(ccxx);

					if( channel_child->getNodeType() &&  // true is not NULL
							channel_child->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
					{
						// Found node which is an Element. Re-cast node as element
						DOMElement* child_Element = dynamic_cast< xercesc::DOMElement* >( channel_child );

						if ( XMLString::equals(child_Element->getTagName(), TAG_xres))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							sscanf(valTagText, "%u", &uisReadVal);
							m_xres = (unsigned short)uisReadVal;
							std::cout << m_xres << "\n";
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_yres))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							sscanf(valTagText, "%u", &uisReadVal);
							m_yres = (unsigned short)uisReadVal;
							std::cout << m_yres << "\n";
							XMLString::release(&valTagText);
						}
					}
				}
			}
		}
	}
}

unsigned short mglAppConfiguration::getYRes()
{
	return m_yres;
}

unsigned short mglAppConfiguration::getXRes()
{
	return m_xres;
}

