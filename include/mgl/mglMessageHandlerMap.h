/*
 * mglBase.h
 *
 *  Created on: 5.01.2017
 *      Author: chuhlich
 */


#ifndef H_MGL_MESSAGEHANDLERMAP
#define H_MGL_MESSAGEHANDLERMAP

#include <stdio.h>
#include <vector>
#include <queue>

#include "mglLogger.h"
#include "mglMessage.h"
#include "mglMessageHandler.h"
#include "mglMessageHandlerMap.h"

#include <json.hpp>
#include "mglValString.h"

using json = nlohmann::json;
using namespace std;


class mglMessageHandlerMap
{
 public:
  void addHandler(mglValString, shared_ptr<mglMessageHandler>);
  int process(std::shared_ptr<mglMessage>);
  
 private:
  map<mglValString, vector< shared_ptr<mglMessageHandler> > > theMap;
  
};



#endif
