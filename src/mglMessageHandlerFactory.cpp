/*
 * mglGuiActionFunctorFactory.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#include <mglMessageHandlerFactory.h>
#include <stdio.h>
#include "mglSystem.h"



mglMessageHandlerFactory::mglMessageHandlerFactory()
{
}

mglMessageHandlerFactory::~mglMessageHandlerFactory()
{
}

/*
 * For the first time the standard object factory can only return mglWindow!
 */
shared_ptr<mglObject> mglMessageHandlerFactory::createObject(mglValString* classname, json configuration)
{
	if (classname->str()->compare("mglGuiAction") == 0)
		return shared_ptr<mglMessageHandler>(new mglMessageHandler());

	return NULL;
}

