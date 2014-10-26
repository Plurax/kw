/*
 * mglAppConfiguration.cpp
 *
 *  Created on: 19.01.2014
 *      Author: cromas
 */

#include "mglAppConfiguration.h"
#include "mglDebug/mglLogger.h"

void mglAppConfiguration::init(DOMNode* appconfig)
{
	INIT_LOG("mglAppConfiguration", "init(DOMNode* appconfig)");

	DOMNodeList*      children = appconfig->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_GL = XMLString::transcode("GL");
	XMLCh* TAG_yres = XMLString::transcode("yres");
	XMLCh* TAG_xres = XMLString::transcode("xres");

	XMLCh* TAG_contextanimationclass = XMLString::transcode("ContextAnimationClass");
	XMLCh* TAG_contextanimationlib = XMLString::transcode("ContextAnimationLib");
	XMLCh* TAG_ContextDelayStart = XMLString::transcode("ContextDelayStart");
	XMLCh* TAG_ContextDelayEnd = XMLString::transcode("ContextDelayEnd");
	XMLCh* TAG_FullScreen = XMLString::transcode("FullScreen");

	unsigned long int uisReadVal = 0;
	char* valTagText;

	m_contextDelayStart = 10;
	m_contextDelayEnd = 10;


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
							sscanf(valTagText, "%lu", &uisReadVal);
							m_xres = (unsigned short)uisReadVal;
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_yres))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							sscanf(valTagText, "%lu", &uisReadVal);
							m_yres = (unsigned short)uisReadVal;
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_contextanimationclass))
						{
							m_ContextAnimationClass = new mglValString(XMLString::transcode(child_Element->getTextContent()));
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_contextanimationlib))
						{
							m_ContextAnimationLib = new mglValString(XMLString::transcode(child_Element->getTextContent()));
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_ContextDelayStart))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							sscanf(valTagText, "%lu", &uisReadVal);
							m_contextDelayStart = uisReadVal;
							LOG_DEBUG("DelayStart: " << m_contextDelayStart);
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_ContextDelayEnd))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							sscanf(valTagText, "%lu", &uisReadVal);
							m_contextDelayEnd = uisReadVal;
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_FullScreen))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							sscanf(valTagText, "%lu", &uisReadVal);
							if (uisReadVal > 0)
								m_FullScreen = true;
							else
								m_FullScreen = false;
							XMLString::release(&valTagText);
						}
					}
				}
			}
		}
	}

	XMLString::release(&TAG_GL);
	XMLString::release(&TAG_yres);
	XMLString::release(&TAG_xres);

	XMLString::release(&TAG_contextanimationclass);
	XMLString::release(&TAG_contextanimationlib);
	XMLString::release(&TAG_ContextDelayStart);
	XMLString::release(&TAG_ContextDelayEnd);
	XMLString::release(&TAG_FullScreen);


	LOG_TRACE("yres: " << m_yres << " xres: " << m_xres);
}

unsigned short mglAppConfiguration::getYRes()
{
	return m_yres;
}

unsigned short mglAppConfiguration::getXRes()
{
	return m_xres;
}


bool mglAppConfiguration::getFullScreen()
{
	return m_FullScreen;
}

mglValString* mglAppConfiguration::getContextAnimationClass()
{
	return m_ContextAnimationClass;
}

mglValString* mglAppConfiguration::getContextAnimationLib()
{
	return m_ContextAnimationLib;
}

unsigned long mglAppConfiguration::getContextAnimationDelayStart()
{
	return m_contextDelayStart;
}

unsigned long mglAppConfiguration::getContextAnimationDelayEnd()
{
	return m_contextDelayEnd;
}


