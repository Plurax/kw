/*
 * mglGuiActionFctLibHandle.h
 *
 *  Created on: 17.02.2014
 *      Author: cromas
 */

#ifndef MGLGUIACTIONFCTLIBHANDLE_H_
#define MGLGUIACTIONFCTLIBHANDLE_H_




#include "mglLibHandle.h"
#include "mglGui/mglGuiActionFactory.h"

class mglGuiActionLibHandle : public mglLibHandle
{
public:
	mglGuiActionLibHandle(void* handle, mglLibraryInfo* libinfo, mglGuiActionFactory* factory);

	mglGuiActionFactory* m_factory;
};




#endif /* MGLGUIACTIONFCTLIBHANDLE_H_ */
