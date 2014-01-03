


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

void mglLogger::configure(DOMElement* loggerconfig)
{
	DOMNodeList*      children = loggerconfig->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_channel = XMLString::transcode("channel");
	XMLCh* TAG_classes = XMLString::transcode("classes");
	XMLCh* TAG_class = XMLString::transcode("class");
	XMLCh* TAG_libraries= XMLString::transcode("libraries");
	XMLCh* TAG_library = XMLString::transcode("library");

	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
/*
			if ( XMLString::equals(currentElement->getTagName(), TAG_xpos))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				x = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_ypos))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				y = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_width))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				width = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_height))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				height = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_string))
			{
				label = std::string(XMLString::transcode(currentElement->getTextContent()));
			}
			*/
		}
	}
}


void mglLogger::log(int level, static_log_info* info, stringstream& line)
{
	vector<mglLogChannel>::iterator itChannels;
//	for (itChannels = m_Channels.begin(); itChannels != m_Channels.end(); itChannels++)
//		itChannels->log(line);
	cout << line.str() << "\n";
}

bool mglLogger::Clear(void)
{
	return true;
}
