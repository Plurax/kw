/*
 * mglGuiActionFunctorFactory.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include <mglMessageHandlerFactory.h>
#include <stdio.h>
#include "mglSystem.h"

/*
 * For the first time the standard object factory can only return mglWindow!
 */
mglMessageHandler* mglMessageHandlerFactory::createMessageHandler(mglValString* classname)
{
	if (classname->str()->compare("mglGuiAction") == 0)
		return new mglMessageHandler();

	return NULL;
}


mglLibraryInfo* mglMessageHandlerFactory::getLibInfo()
{
	return mglSystem::Inst().m_libInfo;
}


mglMessageHandlerFactory::~mglMessageHandlerFactory()
{}
