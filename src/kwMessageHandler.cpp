/*
 * kwGuiActinFunctor.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#include "kwLogger.h"
#include "kwMessageHandler.h"
#include "kwMessage.h"



kwMessageHandler::kwMessageHandler()
{
}

kwMessageHandler::~kwMessageHandler()
{
}


shared_ptr<kwMessage> kwMessageHandler::operator () (shared_ptr<kwMessage> message)
{
	LOG_TRACE << "Testfunction called!";

 	return nullptr;
}





