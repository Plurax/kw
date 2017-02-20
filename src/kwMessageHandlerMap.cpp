/*
 * kwMessageHandlerMap.cpp
 *
 *  Created on: 5.1.2017
 *      Author: chuhlich
 */

#include "kwMessageHandlerMap.h"


using namespace std;

void kwMessageHandlerMap::addHandler(kwValString messageId, shared_ptr<kwMessageHandler> handler)
{
  kwMessageHandlerMap::iterator findIt = theMap.find(messageId);

  std::vector v;
  
  // The ID is already registered - so we need to append the handler to the vector
  if (findIt == m_mMessageHandlers.end())
  {
    v.push_back(handler);
    insert(std::pair<kwValString, std::vector< shared_ptr<kwMessageHandler> > >(messageId, v));
  }
  else
  {
    fintIt.second.push_back(handler);
  }  
}

/**
 * Send the message to all subscribers
 */
int kwMessageHandlerMap::process(shared_ptr<kwMessage> message) 
{
  kwMessageHandlerMap::iterator findIt = theMap.find(processing->getMessageType());
  
  if (findIt != m_mMessageHandlers.end())
  {
    for ( auto &item : fintIt->second)
    {
      // This will execute the handler
      (*item)(message);
    }
  }
}

