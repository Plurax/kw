/*
 * mglLibHandle.cpp
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#include "mglLibHandle.h"

mglLibHandle::mglLibHandle(void* handle, mglLibraryInfo* libinfo)
{
	m_LibraryInfo = libinfo;
}

mglLibHandle::~mglLibHandle()
{

}
