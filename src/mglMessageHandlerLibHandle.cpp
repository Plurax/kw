/*
 * mglGuiActionFctLibHandle.cpp
 *
 *  Created on: 17.02.2014
 *      Author: cromas
 */





#include <mglMessageHandlerLibHandle.h>

mglMessageHandlerLibHandle::mglMessageHandlerLibHandle(void* handle, mglLibraryInfo* libinfo, mglMessageHandlerFactory* factory)
: mglLibHandle(handle, libinfo)
{
	m_factory = factory;
}
