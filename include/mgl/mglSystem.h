/*
 * mglBase.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */


#ifndef H_MGL_SYSTEM
#define H_MGL_SYSTEM

#include <stdio.h>
#include <vector>
#include <queue>

#include "mglTimer.h"
#include "mglLogger.h"
#include "mglLibraryManager.h"
#include "mglSystem.h"
#include "mglBase.h"
#include "mglMessage.h"
#include "mglMessageHandler.h"
#include "mglDataSource.h"

#include <json.hpp>
#include "mglValString.h"

#include "mglLibHandle.h"

class mglGuiObject;

typedef map<int, shared_ptr<mglMessageHandler>> mglMessageHandlerMap;

using json = nlohmann::json;
using namespace std;

class mglSystem
{
public:
	void init(mglValString& configfile);

	~mglSystem();

	static mglSystem& Inst()
	{
		/* This is a windows hack to get the mglSystem instance of 
		the main executable accessible within the DLLs
		Linux OS should work out of the box because we load shared libs with global symbols
		available. So the singleton will be unique even in shared object code access.
		*/
#ifdef _USRDLL
		typedef mglSystem* (*GetSystemFn)();
		HMODULE mod = GetModuleHandle(NULL);
		GetSystemFn getSystem = (GetSystemFn)::GetProcAddress(mod, "GetSystem");
		mglSystem* _instance = getSystem();
		return *_instance;
#else
		static mglSystem _instance;
		return _instance;
#endif
	}

	void destroy();

	void readConfiguration(mglValString& configFile);

	mglMessageHandlerMap m_mMessageHandlers;

	mglDataSourceMap m_DataSources;

	shared_ptr<mglDataSource> getDataSource(mglValString _name);

	mglLibraryInfo* m_libInfo;

	void processEvents();
	void addMessage(shared_ptr<mglMessage> mess);

	void setMessageHandlers(json messageconfig);

	// On windows we force to use UTF8 - so we need to create a seperate Transcoder!
#ifdef WIN32
	XMLTranscoder* UTF8_TRANSCODER = NULL;
#endif
private:
	int m_pixelformat;

	mglSystem();

//    XMLCh* m_TAG_root;

    void createDataLayer(json currentElement);

	queue<shared_ptr<mglMessage>> m_MessageQueue;
};



#endif
