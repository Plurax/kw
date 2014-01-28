/*
 * mglGuiActinFunctor.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "mglLogger/mglLogger.h"
#include "mglGui/mglGuiActionFunctor.h"
#include "mglMessage.h"



mglGuiActionFunctor::mglGuiActionFunctor()
{
}


mglMessage* mglGuiActionFunctor::operator () (mglMessage* message)
{
	INIT_LOG("mglGuiActionFunctor", "operator() (mglMessage* message)");
	LOG_TRACE("Testfunction called!");

	return NULL;
}





