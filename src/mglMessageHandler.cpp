/*
 * mglGuiActinFunctor.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "mglLogger.h"
#include "mglMessageHandler.h"
#include "mglMessage.h"



mglMessageHandler::mglMessageHandler()
{
}

mglMessageHandler::~mglMessageHandler()
{
}


shared_ptr<mglMessage> mglMessageHandler::operator () (shared_ptr<mglMessage> message)
{
	LOG_TRACE << "Testfunction called!";

 	return nullptr;
}





