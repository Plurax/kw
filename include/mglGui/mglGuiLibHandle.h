/*
 * mglGuiLibHandle.h
 *
 *  Created on: 13.02.2014
 *      Author: cromas
 */

#ifndef MGLGUILIBHANDLE_H_
#define MGLGUILIBHANDLE_H_




#include "mglLibHandle.h"
#include "mglGui/mglGuiObjectFactory.h"

class mglGuiLibHandle : public mglLibHandle
{
public:
	mglGuiLibHandle(void* handle, mglLibraryInfo* libinfo, mglGuiObjectFactory* factory);

	mglGuiObjectFactory* m_factory;
};



#endif /* MGLGUILIBHANDLE_H_ */
