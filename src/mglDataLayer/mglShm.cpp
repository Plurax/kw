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

mglShm::mglShm(long key, unsigned long _size)
{
	  /* Create unique key via call to ftok() */
	  key = (key_t)6728;

	  /* Open the shared memory segment - create if necessary */
	  if((shmid = shmget(key, _size, IPC_CREAT | 0666)) == -1)
	    {
	      printf("Shared memory segment exists - opening as client\n");

	      /* Segment probably already exists - try as a client */
	      if((shmid = shmget(key, _size, 0)) == -1)
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
	  if((segptr = (char *)shmat(shmid, 0, 0)) == (char *)-1)
	    {
	      perror("shmat");
	      exit(1);
	    }

}

char* getPtr();
bool lockSegment();
bool unlockSegment();
bool isLocked();

