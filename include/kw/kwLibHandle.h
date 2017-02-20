/*
 * kwLibHandle.h
 *
 *  Created on: 12.10.2013
 *      Author: chuhlich
 */

#ifndef KWLIBHANDLE_H_
#define KWLIBHANDLE_H_

#include "kwValString.h"
#include "kwLibraryInfo.h"
#include "kwObjectFactory.h"

using namespace std;


class kwLibHandle
{
public:
	kwLibHandle(void* handle, kwLibraryInfo* libinfo);
	~kwLibHandle();
	kwLibraryInfo* getInfo();

	void addFactory(kwObjectFactory* factory, kwValString type);
	
	kwObjectFactory* getFactory(kwValString type);

protected:
	void* m_handle;
	kwLibraryInfo* m_LibraryInfo;

	// A map which maps types to their factories
	map<kwValString, kwObjectFactory*> m_ObjectFactories;
};
typedef kwLibraryInfo* (*LibInfoRetrieveFunc)();

#endif /* KWLIBHANDLE_H_ */
