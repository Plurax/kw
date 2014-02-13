/*
 * mglDataLibHandle.h
 *
 *  Created on: 13.02.2014
 *      Author: cromas
 */

#ifndef MGLDATALIBHANDLE_H_
#define MGLDATALIBHANDLE_H_


#include "mglLibHandle.h"
#include "mglDataLayer/mglDataSourceFactory.h"

class mglDataLibHandle : public mglLibHandle
{
public:
	mglDataLibHandle(void* handle, mglLibraryInfo* libinfo, mglDataSourceFactory* factory);

	mglDataSourceFactory* m_factory;
};


#endif /* MGLDATALIBHANDLE_H_ */
