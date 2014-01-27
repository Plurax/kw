/*
 * mglShm.h
 *
 *  Created on: 27.01.2014
 *      Author: cromas
 */

#ifndef MGLSHM_H_
#define MGLSHM_H_

class mglShm
{
public:
	mglShm(long key, unsigned long _size);

	char* getPtr();
	bool lockSegment();
	bool unlockSegment();
	bool isLocked();
private:
	  key_t key;
	  int   shmid;
	  char  *segptr;
};

#endif /* MGLSHM_H_ */
