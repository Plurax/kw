/*
 * mglSocket.cpp
 *
 *  Created on: 26.04.2014
 *      Author: cromas
 */


#include "mglDataLayer/mglSocket.h"
#include "mglDebug/mglDebug.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>

using namespace std;

mglSocket::mglSocket(DOMElement* configuration)
{
	INIT_LOG("mglSocket", "mglSocket");

	DOMNodeList*      children = configuration->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_port = XMLString::transcode("port");
	XMLCh* TAG_host = XMLString::transcode("host");

	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );

			if ( XMLString::equals(currentElement->getTagName(), TAG_port))
			{
				char* xstr = XMLString::transcode(currentElement->getTextContent());
				m_Port = atoi(xstr);
				XMLString::release(&xstr);
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_host))
			{
				char* xstr = XMLString::transcode(currentElement->getTextContent());
				m_Host = new mglValString(xstr);
				XMLString::release(&xstr);
			}
		}
	}

	XMLString::release(&TAG_host);
	XMLString::release(&TAG_port);

	m_SocketFd = -1; // initial fail state

	LOG_TRACE("Init Socket for Port " << m_Port << " on Host " << m_Host->str()->c_str());
}


void mglSocket::init()
{
	INIT_LOG("mglSocket", "void init()");

    socklen_t clilen;
    char buffer[256];
    int n;

    m_SocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_SocketFd < 0)
       LOG_TRACE("ERROR opening socket");
    bzero((char *) &m_Serv_addr, sizeof(m_Serv_addr));

    m_Server = gethostbyname(m_Host->str()->c_str());

    m_Serv_addr.sin_family = AF_INET;
    bcopy((char *)m_Server->h_addr,
             (char *)&m_Serv_addr.sin_addr.s_addr,
             m_Server->h_length);

    m_Serv_addr.sin_port = htons(m_Port);

    /*
    if (bind(m_SocketFd, (struct sockaddr *) &m_Serv_addr,
             sizeof(m_Serv_addr)) < 0)
             LOG_TRACE("ERROR connecting");
*/
	if (connect(m_SocketFd, (struct sockaddr *) &m_Serv_addr,
             sizeof(m_Serv_addr)) < 0)
        LOG_TRACE("ERROR connecting");

    LOG_TRACE("Socket with Host " << m_Host->str()->c_str() << " and Port " << m_Port << " created...");

}

/**
 * Wrapper for the write function.
 * Simple applications should not use this function as the class
 * provides sendRequest for CLI like behaviour.
 *
 * @param buff
 * @param len
 * @return
 */
int mglSocket::write(char *buff, int len)
{
	INIT_LOG("mglSocket", "write(char* buff, size_t len");
	return ::write(m_SocketFd, buff, strlen(buff));

}

/**
 * Wrapper for the read function.
 * Simple applications should not use this function as the class
 * provides sendRequest for CLI like behaviour.
 *
 * @param buff
 * @param maxlen
 * @return
 */
int mglSocket::read(char *buff, size_t maxlen)
{
	return ::read(m_SocketFd, buff, maxlen);
}


void mglSocket::deInit()
{
	close(m_SocketFd);
}

/**
 * This function sends a specific request as a ValString to the server
 * and returns the complete response as a ValString.
 * @param request
 * @return
 */
mglValString mglSocket::sendRequest(mglValString* request)
{
	INIT_LOG("mglSocket", "mglValString sendRequest(mglValString* request)");

	LOG_TRACE("Sending request: " << request->str()->c_str());
	char* reception_buffer = new char[1024];
	unsigned int complete_size = 0;
	ssize_t rec = 1;

	// send the request
	::write(m_SocketFd, request->str()->c_str(), strlen(request->str()->c_str()));

	bzero((char *) reception_buffer, sizeof(reception_buffer));

	// Read into the reception buffer
	while (rec != 0)
	{
		LOG_TRACE("Entering while");
		// every run we read exactly 1 char - this is not fast - but works for the first try
		rec = ::read(m_SocketFd, reception_buffer, 1023);
		if (rec == -1)
		{
			perror("Error on read from Socket: ");
			THROW_TECHNICAL_EXCEPTION(1234, "Error on read from Socket: ");
		}
		if (rec > 0)
		{
			complete_size += rec;
			if (reception_buffer[complete_size - 1] == '\0')
				break;
		}
	}

	return mglValString(reception_buffer);
}
