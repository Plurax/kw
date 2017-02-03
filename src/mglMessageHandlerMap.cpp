/*
 * mglMessageHandlerMap.cpp
 *
 *  Created on: 5.1.2017
 *      Author: chuhlich
 */

#include "mglMessageHandlerMap.h"


using namespace std;

void mglMessageHandlerMap::addHandler(mglValString messageId, shared_ptr<mglMessageHandler> handler)
{
  mglMessageHandlerMap::iterator findIt = theMap.find(messageId);

  std::vector v;
  
  // The ID is already registered - so we need to append the handler to the vector
  if (findIt == m_mMessageHandlers.end())
  {
    v.push_back(handler);
    insert(std::pair<mglValString, std::vector< shared_ptr<mglMessageHandler> > >(messageId, v));
  }
  else
  {
    fintIt.second.push_back(handler);
  }  
}

/**
 * Send the message to all subscribers
 */
int mglMessageHandlerMap::process(shared_ptr<mglMessage> message) 
{
  mglMessageHandlerMap::iterator findIt = theMap.find(processing->getMessageType());
  
  if (findIt != m_mMessageHandlers.end())
  {
    for ( auto &item : fintIt->second)
    {
      // This will execute the handler
      (*item)(message);
    }
  }
}

