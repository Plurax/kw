/*
 * mglMessageHandlerLibManager.h
 *
 *  Created on: 08.02.2015
 *      Author: cromas
 */

#ifndef MGLLIBRARYMANAGER_H_
#define MGLLIBRARYMANAGER_H_

#include "mglObject.h"
#include "mglLibHandle.h"
#include "json.hpp"


#ifdef WIN32
#include "Windows.h"
#else
#include <dlfcn.h>
#endif

using json = nlohmann::json;

class mglLibraryManager
{
public:
	~mglLibraryManager();

	static mglLibraryManager& Inst()
	{
		static mglLibraryManager _instance;
		return _instance;
	};

	void init();

	// Create an object
	shared_ptr<mglObject> createObject(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname, shared_ptr<mglValString> main_classname, json configuration);

private:
	map<mglValString, shared_ptr<mglLibHandle>> m_loadedLibraries;
};


#endif /* MGLLIBRARYMANAGER_H_ */
