/*
 * mglGuiLibHandle.cpp
 *
 *  Created on: 13.02.2014
 *      Author: cromas
 */


#include "mglGui/mglGuiLibHandle.h"

mglGuiLibHandle::mglGuiLibHandle(void* handle, mglLibraryInfo* libinfo, mglGuiObjectFactory* factory)
: mglLibHandle(handle, libinfo)
{
	m_factory = factory;
}
