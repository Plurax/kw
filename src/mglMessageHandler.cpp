/*
 * mglGuiActinFunctor.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "mglDebug/mglLogger.h"
#include "mglMessageHandler.h"
#include "mglMessage.h"



mglMessageHandler::mglMessageHandler()
{
}


mglMessage* mglMessageHandler::operator () (mglMessage* message)
{
	INIT_LOG("mglGuiActionFunctor", "operator() (mglMessage* message)");
	LOG_TRACE("Testfunction called!");

	return NULL;
}





