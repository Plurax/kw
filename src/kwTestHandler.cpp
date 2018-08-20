/*
 * kwTestHandler.cpp
 *
 *  Created on: 18.12.2013
 *      Author: cromas
 */


#include "kw/kwLogger.h"
#include "kw/kwSystem.h"
#include "kwTestHandler.h"

kwTestHandler::kwTestHandler()
{
}


shared_ptr<kwMessage> kwTestHandler::operator () (shared_ptr<kwMessage> message)
{
  LOG_TRACE << "Message Text: " << *(message->getMessageText());
  LOG_TRACE << "JSON Payload: " << message->getJsonObj().dump();

  return nullptr;
}


