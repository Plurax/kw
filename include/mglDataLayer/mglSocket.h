/*
 * mglSocket.h
 *
 *  Created on: 26.04.2014
 *      Author: cromas
 */

#ifndef MGLSOCKET_H_
#define MGLSOCKET_H_

#include "mglDataSource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

using namespace std;
using namespace xercesc;

class mglSocket : public mglDataSource
{
public:
	mglSocket(DOMElement* configuration);

	void init();
	void deInit();

	int write(char *buff, int len);
	int read(char *buff, size_t);

	mglValString sendRequest(mglValString* request);
private:
	int m_Status;
	int m_SocketFd;
	int m_Port;
    struct hostent *m_Server;
	mglValString* m_Host;

    struct sockaddr_in m_Serv_addr, m_Cli_addr;
   int m_Size;
};


#endif /* MGLSOCKET_H_ */
