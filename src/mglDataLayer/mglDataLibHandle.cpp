/*
 * mglDataLibHandle.cpp
 *
 *  Created on: 13.02.2014
 *      Author: cromas
 */




#include "mglDataLayer/mglDataLibHandle.h"

mglDataLibHandle::mglDataLibHandle(void* handle, mglLibraryInfo* libinfo, mglDataSourceFactory* factory)
: mglLibHandle(handle, libinfo)
{
	m_factory = factory;
}
