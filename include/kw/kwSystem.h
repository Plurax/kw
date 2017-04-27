/*
 * kwBase.h
 *
 *  Created on: 12.10.2013
 *      Author: chuhlich
 */


#ifndef H_KW_SYSTEM
#define H_KW_SYSTEM

#include <stdio.h>
#include <vector>
#include <queue>

#include "kwTimer.h"
#include "kwLogger.h"
#include "kwLibraryManager.h"
#include "kwSystem.h"
#include "kwBase.h"
#include "kwMessage.h"
#include "kwMessageHandler.h"
#include "kwDataSource.h"

#include <json.hpp>
#include "kwValString.h"
#include "kwLockedQueue.h"

#include "kwLibHandle.h"

class kwGuiObject;

typedef map<int, shared_ptr<kwMessageHandler>> kwMessageHandlerMap;

using json = nlohmann::json;
using namespace std;

class kwSystem
{
 public:
  void init(kwValString& configfile);

  ~kwSystem();

  static kwSystem& Inst()
  {
    /* This is a windows hack to get the kwSystem instance of 
       the main executable accessible within the DLLs
       Linux OS should work out of the box because we load shared libs with global symbols
       available. So the singleton will be unique even in shared object code access.
    */
#ifdef _USRDLL
    typedef kwSystem* (*GetSystemFn)();
    HMODULE mod = GetModuleHandle(NULL);
    GetSystemFn getSystem = (GetSystemFn)::GetProcAddress(mod, "GetSystem");
    kwSystem* _instance = getSystem();
    return *_instance;
#else
    static kwSystem _instance;
    return _instance;
#endif
  }

  void destroy();

  void readConfiguration(kwValString& configFile);

  kwMessageHandlerMap m_mMessageHandlers;

  kwDataSourceMap m_DataSources;

  shared_ptr<kwDataSource> getDataSource(kwValString _name);

  kwLibraryInfo* m_libInfo;

  void processMessages();
  void addMessage(shared_ptr<kwMessage> mess);
  void pollTimers();
  
  void setMessageHandlers(json messageconfig);

#ifdef WIN32

#endif
 private:
  kwSystem();

  void createDataLayer(json currentElement);
  void createTimers(json timerconfig);
  
  vector<shared_ptr<kwLockedQueue<std::shared_ptr<kwMessage>>>> m_MessageQueues;
  vector<shared_ptr<kwLockedQueue<std::shared_ptr<kwMessage>>>> m_ThreadedMessageQueues;

  vector<shared_ptr<kwTimer>> m_Timers;
};



#endif
