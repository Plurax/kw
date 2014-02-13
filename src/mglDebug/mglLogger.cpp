


#include "mglDebug/mglLogger.h"
#include "mglDebug/mglLogChannel.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace xercesc;

mglLogger::~mglLogger()
{
}

mglLogger::mglLogger()
{
	m_isInitialized = false;
	for (int i = 0; i < DEF_MAX_LOG_CHANNELS; i++)
		m_Channels[i] = NULL;
}


void mglLogger::configure(DOMNode* loggerconfig)
{
	DOMNodeList*      children = loggerconfig->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_Channel = XMLString::transcode("Channel");
	XMLCh* TAG_stream = XMLString::transcode("stream");
	XMLCh* TAG_mask = XMLString::transcode("mask");
	XMLCh* TAG_libraries= XMLString::transcode("libraries");
	XMLCh* TAG_classes = XMLString::transcode("classes");

	int iChannelCount = 0; // Count number of channels - we only allow up to 5 channels
	unsigned short uisReadVal = 0;
	unsigned int ui;
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

			if ( XMLString::equals(currentElement->getTagName(), TAG_Channel))
			{
				if (iChannelCount >= DEF_MAX_LOG_CHANNELS)
					continue; // ignore additional log channel settings

				DOMNodeList* channel_children = currentElement->getChildNodes();
				for( XMLSize_t ccxx = 0; ccxx < channel_children->getLength(); ++ccxx )
				{
					DOMNode* channel_child= channel_children->item(ccxx);

					if( channel_child->getNodeType() &&  // true is not NULL
							channel_child->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
					{
						// Found node which is an Element. Re-cast node as element
						DOMElement* child_Element = dynamic_cast< xercesc::DOMElement* >( channel_child );

						if ( XMLString::equals(child_Element->getTagName(), TAG_stream))
						{
							m_Channels[iChannelCount] = new mglLogChannel(std::string(XMLString::transcode(child_Element->getTextContent())));
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_mask))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							if ((valTagText[0] == '0') && (valTagText[1] == 'x'))
								sscanf(valTagText, "0x%x", &ui);
							else
								sscanf(valTagText, "%u", &ui);
							uisReadVal = (unsigned short)ui;
							m_Channels[iChannelCount]->setMask(uisReadVal);
							XMLString::release(&valTagText);
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_classes))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							char* prevPtr = valTagText;
							char* nextPtr = valTagText;

							while (NULL != nextPtr)
							{
								nextPtr = strchr(valTagText, ',');

								if (nextPtr)
									*nextPtr = '\0';

								string newClass = string(prevPtr);
								m_Channels[iChannelCount]->addClassFilter(newClass, 0xfFff);
								if (nextPtr)
								{
									nextPtr++;
									prevPtr = nextPtr;
								}
							}
						}


						if ( XMLString::equals(child_Element->getTagName(), TAG_libraries))
						{
							valTagText = XMLString::transcode(child_Element->getTextContent());
							char* prevPtr = valTagText;
							char* nextPtr = valTagText;

							while (NULL != nextPtr)
							{
								nextPtr = strchr(valTagText, ',');

								if (nextPtr)
									*nextPtr = '\0';

								string newLib = string(prevPtr);
								m_Channels[iChannelCount]->addLibraryFilter(newLib, 0xFFFF);

								if (nextPtr)
								{
									nextPtr++;
									prevPtr = nextPtr;
								}
							}
						}
					}
				}
				iChannelCount++;
			}
		}
	}
	m_isInitialized = true;
}


void mglLogger::log(unsigned short level, static_log_info* info, stringstream& line)
{
	if (!m_isInitialized)
		return;

	for (int i = 0; i < DEF_MAX_LOG_CHANNELS; i++)
	{
		if (m_Channels[i]) // channel is defined?
		{
			if (m_Channels[i]->getMask() & level) // log level is in the mask?
			{
				if (m_Channels[i]->getLibraryFilter(info->psz_libname) & level)
					if (m_Channels[i]->getClassFilter(info->psz_classname) & level)
						m_Channels[i]->log(line); // todo class, library and its filters check
			}
		}
	}
}

bool mglLogger::destroy(void)
{
	for (int i = 0; i < DEF_MAX_LOG_CHANNELS; i++)
	{
		if (m_Channels[i])
		{
			delete m_Channels[i];
		}
	}

	return true;
}
