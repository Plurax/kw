/*
 * mglShm.h
 *
 *  Created on: 27.01.2014
 *      Author: cromas
 */

#ifndef MGLSHM_H_
#define MGLSHM_H_

#include "mglDataSource.h"

class mglShm : public mglDataSource
{
public:
	mglShm(long key, unsigned long _size);

	char* getPtr();
	bool lockSegment();
	bool unlockSegment();
	bool isLocked();
private:
	  key_t m_key, m_semkey;
	  int   m_shmid, m_semid;
	  char  *m_segptr;
};

#endif /* MGLSHM_H_ */
