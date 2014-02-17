/*
 * mglGuiActionFctLibHandle.cpp
 *
 *  Created on: 17.02.2014
 *      Author: cromas
 */





#include "mglGui/mglGuiActionLibHandle.h"

mglGuiActionLibHandle::mglGuiActionLibHandle(void* handle, mglLibraryInfo* libinfo, mglGuiActionFactory* factory)
: mglLibHandle(handle, libinfo)
{
	m_factory = factory;
}
