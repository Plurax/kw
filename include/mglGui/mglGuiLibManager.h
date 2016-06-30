/*
 * mglObjectManager.h
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#ifndef MGLOBJECTMANAGER_H_
#define MGLOBJECTMANAGER_H_

#include "mglValues/mglValString.h"
#include <stdio.h>
#include <map>
#include <vector>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdexcept>

#ifdef WIN32
#else
#include <dlfcn.h>
#endif

#include <mglMessageHandlerFactory.h>
#include <mglMessageHandlerLibHandle.h>

#include "mglGui/mglGuiObject.h"
#include "mglGui/mglGuiLibHandle.h"
#include "mglGui/mglGuiObjectFactory.h"

#include <json.hpp>

using namespace std;


class mglGuiLibManager
{
public:
	~mglGuiLibManager();

	static mglGuiLibManager& Inst()
	{
		static mglGuiLibManager _instance;
		return _instance;
	};

	void init();

	shared_ptr<mglGuiObject> createGUIObject(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname, json configuration);
	shared_ptr<mglMessageHandler> createMessageHandler(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname);

private:
	map<mglValString, shared_ptr<mglGuiLibHandle>> m_loadedGuiLibraries;

	map<mglValString, shared_ptr<mglMessageHandlerLibHandle>> m_loadedMessageHandlerLibraries;
};


#endif /* MGLOBJECTMANAGER_H_ */
