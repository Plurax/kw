/*
 * kwSocket.h
 *
 *  Created on: 26.04.2014
 *      Author: chuhlich
 */

#ifndef KWSOCKETCLIENT_H_
#define KWSOCKETCLIENT_H_

#include "kw/kwDataSource.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#ifdef WIN32

#else

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class kwSocketClient : public kwDataSource
{
public:
	kwSocketClient(json configuration);

	void init();
	void deInit();

	int write(char *buff, int len);
	int read(char *buff, size_t);

	kwValString sendRequest(kwValString* request);
private:
	int m_Status;
	int m_SocketFd;
	int m_Port;
    struct hostent *m_Server;
	kwValString* m_Host;

    struct sockaddr_in m_Serv_addr, m_Cli_addr;
   int m_Size;
};

#endif
#endif /* KWSOCKETCLIENT_H_ */
