/*
 * mglLibHandle.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#ifndef MGLLIBHANDLE_H_
#define MGLLIBHANDLE_H_

#include <string>
#include "mglLibraryInfo.h"
using namespace std;


class mglLibHandle
{
public:
	mglLibHandle(void* handle, mglLibraryInfo* libinfo);
	~mglLibHandle();

protected:
	void* m_handle;
	mglLibraryInfo* m_LibraryInfo;
};
typedef mglLibraryInfo* (*LibInfoRetrieveFunc)();

#endif /* MGLLIBHANDLE_H_ */
