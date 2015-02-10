/*
 * mglGuiActionFctLibHandle.h
 *
 *  Created on: 17.02.2014
 *      Author: cromas
 */

#ifndef MGLGUIACTIONFCTLIBHANDLE_H_
#define MGLGUIACTIONFCTLIBHANDLE_H_




#include <mglMessageHandlerFactory.h>
#include "mglLibHandle.h"

class mglMessageHandlerLibHandle : public mglLibHandle
{
public:
	mglMessageHandlerLibHandle(void* handle, mglLibraryInfo* libinfo, mglMessageHandlerFactory* factory);

	mglMessageHandlerFactory* m_factory;
};




#endif /* MGLGUIACTIONFCTLIBHANDLE_H_ */
