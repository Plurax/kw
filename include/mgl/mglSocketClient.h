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
#include <sys/types.h>

#ifdef WIN32
#else

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <json.hpp>

using namespace std;
using json = nlohmann::json;

class mglSocketClient : public mglDataSource
{
public:
	mglSocketClient(json configuration);

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

#endif
#endif /* MGLSOCKET_H_ */
