/*
 * kwBase.h
 *
 *  Created on: 5.01.2017
 *      Author: chuhlich
 */


#ifndef H_KW_MESSAGEHANDLERMAP
#define H_KW_MESSAGEHANDLERMAP

#include <stdio.h>
#include <vector>
#include <queue>

#include "kwLogger.h"
#include "kwMessage.h"
#include "kwMessageHandler.h"
#include "kwMessageHandlerMap.h"

#include <nlohmann/json.hpp>
#include "kwValString.h"

using json = nlohmann::json;
using namespace std;


class kwMessageHandlerMap
{
 public:
  void addHandler(kwValString, shared_ptr<kwMessageHandler>);
  int process(std::shared_ptr<kwMessage>);
  
 private:
  map<kwValString, vector< shared_ptr<kwMessageHandler> > > theMap;
  
};



#endif
