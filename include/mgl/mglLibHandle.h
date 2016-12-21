/*
 * mglLibHandle.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#ifndef MGLLIBHANDLE_H_
#define MGLLIBHANDLE_H_

#include "mglValString.h"
#include "mglLibraryInfo.h"
#include "mglObjectFactory.h"

using namespace std;


class mglLibHandle
{
public:
	mglLibHandle(void* handle, mglLibraryInfo* libinfo);
	~mglLibHandle();
	mglLibraryInfo* getInfo();

	void addFactory(mglObjectFactory* factory, mglValString type);
	
	mglObjectFactory* getFactory(mglValString type);

protected:
	void* m_handle;
	mglLibraryInfo* m_LibraryInfo;

	// A map which maps types to their factories
	map<mglValString, mglObjectFactory*> m_ObjectFactories;
};
typedef mglLibraryInfo* (*LibInfoRetrieveFunc)();

#endif /* MGLLIBHANDLE_H_ */
