/*
 * mglSocket.cpp
 *
 *  Created on: 26.04.2014
 *      Author: cromas
 */


#include "mglDebug/mglDebug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <mglDataLayer/mglSocketClient.h>

#ifdef WIN32
#else

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;

mglSocketClient::mglSocketClient(json configuration)
{
	INIT_LOG("mglSocket", "mglSocket");

	for (json::iterator it = configuration.begin(); it != configuration.end(); ++it) 
	{
		string str = configuration["port"];
		const char* xstr = str.c_str();
		m_Port = atoi(xstr);
		
		str = configuration["port"];
		xstr = str.c_str();
		m_Host = new mglValString(xstr);
	}

	m_SocketFd = -1; // initial fail state

	LOG_TRACE("Init Socket for Port " << m_Port << " on Host " << *m_Host);
}

/**
 * This fits to the interface but it does nothing because
 * the connection is opened for each request.
 */
void mglSocketClient::init()
{
	INIT_LOG("mglSocket", "void init()");

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
int mglSocketClient::write(char *buff, int len)
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
int mglSocketClient::read(char *buff, size_t maxlen)
{
	return ::read(m_SocketFd, buff, maxlen);
}


void mglSocketClient::deInit()
{
	close(m_SocketFd);
	m_SocketFd = -1;
}

/**
 * This function sends a specific request as a ValString to the server
 * and returns the complete response as a ValString.
 * @param request
 * @return
 */
mglValString mglSocketClient::sendRequest(mglValString* request)
{
	INIT_LOG("mglSocket", "mglValString sendRequest(mglValString* request)");

	LOG_TRACE("Sending request: " << *request);

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

    LOG_TRACE("Socket with Host " << *m_Host << " and Port " << m_Port << " created...");
	char* reception_buffer = new char[1024];
	int complete_size = 0;
	ssize_t rec = 1;

	// send the request
	::write(m_SocketFd, request->str()->c_str(), strlen(request->str()->c_str()));
	::write(m_SocketFd, "\n", 1);

	bzero((char *) reception_buffer, sizeof(reception_buffer));

	// Read into the reception buffer
	while (rec != 0)
	{
		LOG_TRACE("Entering while");
		// every run we read exactly 1 char - this is not fast - but works for the first try
		rec = ::read(m_SocketFd, &reception_buffer[complete_size], 1023 - complete_size);
		if (rec == -1)
		{
			perror("Error on read from Socket: ");
			THROW_TECHNICAL_EXCEPTION(1234, "Error on read from Socket: ");
		}
		if (rec > 0)
		{
			complete_size += rec;
		}
		LOG_TRACE("rec=" << rec);
	}
	reception_buffer[complete_size] = '\0';
	LOG_TRACE(reception_buffer);
	deInit();

	return mglValString(reception_buffer);
}
#endif
