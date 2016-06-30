/*
 * mglShm.cpp
 *
 *  Created on: 27.01.2014
 *      Author: cromas
 */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>


#ifdef WIN32

#else

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
#include <iostream>


#include "mglDataLayer/mglShm.h"
#include "mglDebug/mglLogger.h"
#include "mglValues/mglValString.h"



mglShm::mglShm(json configuration)
{
	INIT_LOG("mglShm", "mglShm");

/*	XMLCh* TAG_key = XMLString::transcode("key");
	XMLCh* TAG_size = XMLString::transcode("size");

	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
			if ( XMLString::equals(currentElement->getTagName(), TAG_key))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				m_key = (key_t)atoi(xstr.c_str());
			}
/*
			if ( XMLString::equals(currentElement->getTagName(), TAG_semkey))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				m_semkey = (key_t)atoi(xstr.c_str());
			}
			if ( XMLString::equals(currentElement->getTagName(), TAG_size))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				m_size = atoi(xstr.c_str());
			}

		}
	}
*/

	LOG_TRACE("Init SHM with key " << m_key << " and size " << m_size);
}

/**
 * This will init the shared memory segment according to the loaded parameters.
 * This is executed after reading the data XML tree.
 */
void mglShm::init()
{
	INIT_LOG("mglShm", "init");

	/* Open the shared memory segment - create if necessary */
	if((m_shmid = shmget(m_key, m_size, IPC_CREAT | 0666)) == -1)
	{
		LOG_TRACE("Shared memory segment exists - opening as client\n");

		  /* Segment probably already exists - try as a client */
		if((m_shmid = shmget(m_key, m_size, 0)) == -1)
		{
		  LOG_ERROR("shmget");
		  exit(1);
		}
	}
	else
	{
		LOG_TRACE("Creating new shared memory segment");
	}

	/* Attach (map) the shared memory segment into the current process */
	if((m_segptr = (char *)shmat(m_shmid, 0, 0)) == (char *)-1)
	{
		LOG_ERROR("shmat");
		exit(1);
	}
}

/**
 * Detaches the shared memory segment and closes it.
 */
void mglShm::deInit()
{
	INIT_LOG("mglShm", "deInit");

	LOG_DEBUG("Detaching SHM key " << m_key << " Detach retcode: " << shmdt(m_segptr));
//	LOG_DEBUG("Delete SHM" << shmctl(m_shmid, IPC_RMID, 0));
}

/**
 * Returns the segment pointer.
 * @return
 */
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

#endif
