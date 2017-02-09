/*
 * mglShm.h
 *
 *  Created on: 27.01.2014
 *      Author: chuhlich
 */

#ifndef MGLSHM_H_
#define MGLSHM_H_

#include "mglDataSource.h"
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

#ifdef WIN32
#else

class mglShm : public mglDataSource
{
public:
	mglShm(json configuration);

	void init();
	void deInit();

	char* getPtr();
	bool lockSegment();
	bool unlockSegment();
	bool isLocked();
private:
#ifndef WIN32
	  key_t m_key, m_semkey;
#endif
	  int   m_shmid, m_semid, m_size;
	  char  *m_segptr;
};

#endif /* MGLSHM_H_ */
#endif
