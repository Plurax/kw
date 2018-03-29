/*
 * kwMessageHandlerLibManager.h
 *
 *  Created on: 08.02.2015
 *      Author: chuhlich
 */

#ifndef KWLIBRARYMANAGER_H_
#define KWLIBRARYMANAGER_H_

#include "kw/kwObject.h"
#include "kw/kwLibHandle.h"
#include "nlohmann/json.hpp"


#ifdef WIN32
#include "Windows.h"
#else
#include <dlfcn.h>
#endif

using json = nlohmann::json;

class kwLibraryManager
{
public:
	~kwLibraryManager();

	static kwLibraryManager& Inst()
	{
		static kwLibraryManager _instance;
		return _instance;
	};

	void init();

	// Create an object
	shared_ptr<kwObject> createObject(shared_ptr<kwValString> libname, shared_ptr<kwValString> classname, shared_ptr<kwValString> main_classname, json configuration);

private:
	map<kwValString, shared_ptr<kwLibHandle>> m_loadedLibraries;
};


#endif /* KWLIBRARYMANAGER_H_ */
