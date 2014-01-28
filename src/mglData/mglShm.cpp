/*
 * mglShm.cpp
 *
 *  Created on: 27.01.2014
 *      Author: cromas
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <ctype.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>


#include "mglDataLayer/mglShm.h"
#include "mglLogger/mglLogger.h"

mglShm::mglShm(long key, unsigned long _size)
{
	INIT_LOG("mglShm", "mglShm");

	/* Create unique key via call to ftok() */
	m_key = (key_t)6728;
	m_semkey = (key_t)6728 + 10;
	/* Open the shared memory segment - create if necessary */
	if((m_shmid = shmget(m_key, _size, IPC_CREAT | 0666)) == -1)
	{
		printf("Shared memory segment exists - opening as client\n");

		  /* Segment probably already exists - try as a client */
		if((m_shmid = shmget(key, _size, 0)) == -1)
		{
		  perror("shmget");
		  exit(1);
		}
	}
	else
	{
		printf("Creating new shared memory segment\n");
	}

	/* Attach (map) the shared memory segment into the current process */
	if((m_segptr = (char *)shmat(m_shmid, 0, 0)) == (char *)-1)
	{
		perror("shmat");
		exit(1);
	}

	// Create semaphore
	m_semid = semget( m_semkey, 1, 0666 | IPC_CREAT | IPC_EXCL );
	if ( m_semid == -1 )
	{
		LOG_TRACE("main: semget() failed\n");
		m_segptr = NULL;
	}
}

char* mglShm::getPtr()
{
	return m_segptr;
}

bool mglShm::lockSegment()
{
	return true;
}

bool mglShm::unlockSegment()
{
	return true;
}

bool mglShm::isLocked()
{
	return false;
}

