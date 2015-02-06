/*
 * mglGuiActinFunctor.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "mglDebug/mglLogger.h"
#include "mglActionFunctor.h"
#include "mglMessage.h"



mglActionFunctor::mglActionFunctor()
{
}


mglMessage* mglActionFunctor::operator () (mglMessage* message)
{
	INIT_LOG("mglGuiActionFunctor", "operator() (mglMessage* message)");
	LOG_TRACE("Testfunction called!");

	return NULL;
}





