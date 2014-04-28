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


int mglSocket::write(char *buff, int len)
{
	INIT_LOG("mglSocket", "write(char* buff, size_t len");
	return ::write(m_SocketFd, buff, strlen(buff));

}

int mglSocket::read(char *buff, size_t maxlen)
{
	return ::read(m_SocketFd, buff, maxlen);
}


void mglSocket::deInit()
{
	close(m_SocketFd);
}


int mglSocket::handleRequest()
{
	INIT_LOG("mglSocket", "int handleRequest()");

	char buffer[256];
	int newsockfd, n;
	socklen_t clilen;
	listen(m_SocketFd,5);
	clilen = sizeof(m_Cli_addr);
	newsockfd = accept(m_SocketFd,
				(struct sockaddr *) &m_Cli_addr,
				&clilen);
	if (newsockfd < 0)
		 LOG_TRACE("ERROR on accept");
	bzero(buffer,256);
	n = ::read(newsockfd,buffer,255);
	if (n < 0)
		LOG_TRACE("ERROR reading from socket");
	printf("Here is the message: %s\n",buffer);
	n = ::write(newsockfd,"I got your message",18);
	if (n < 0)
		LOG_TRACE("ERROR writing to socket");
	close(newsockfd);
}
