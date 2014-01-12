


#include "mglLogger.h"
#include "mglLogChannel.h"
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
	for (int i=0; i<5; i++)
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
				DOMNodeList* channel_children = currentElement->getChildNodes();
				for( XMLSize_t ccxx = 0; ccxx < channel_children->getLength(); ++ccxx )
				{
					if( currentNode->getNodeType() &&  // true is not NULL
							currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
					{
						// Found node which is an Element. Re-cast node as element
						DOMElement* child_Element = dynamic_cast< xercesc::DOMElement* >( currentNode );

						if ( XMLString::equals(child_Element->getTagName(), TAG_stream))
						{
							m_Channels[iChannelCount] = new mglLogChannel(std::string(XMLString::transcode(child_Element->getTextContent())));
						}

						if ( XMLString::equals(child_Element->getTagName(), TAG_mask))
						{
							char* numberstr = XMLString::transcode(child_Element->getTextContent());
							unsigned short uisReadVal = 0;
							if ((numberstr[0] == '0') && (numberstr[0] == 'x'))
								sscanf(numberstr, "0x%hu", &uisReadVal);
							else
								sscanf(numberstr, "%hu", &uisReadVal);

							m_Channels[iChannelCount]->setMask(uisReadVal);
							std::cout << "got mask: " << uisReadVal << "\n";
						}

					}
				}
			}
		}
	}
}


void mglLogger::log(int level, static_log_info* info, stringstream& line)
{
	for (int i=0; i<3; i++)
	{
		if (m_Channels[i])
			m_Channels[i]->log(line);
	}
}

bool mglLogger::Clear(void)
{
	return true;
}
