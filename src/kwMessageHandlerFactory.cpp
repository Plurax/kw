/*
 * kwGuiActionFunctorFactory.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#include <kwMessageHandlerFactory.h>
#include <stdio.h>
#include "kwSystem.h"



kwMessageHandlerFactory::kwMessageHandlerFactory()
{
}

kwMessageHandlerFactory::~kwMessageHandlerFactory()
{
}

/*
 * For the first time the standard object factory can only return kwWindow!
 */
shared_ptr<kwObject> kwMessageHandlerFactory::createObject(kwValString* classname, json configuration)
{
	if (classname->str()->compare("kwGuiAction") == 0)
		return shared_ptr<kwMessageHandler>(new kwMessageHandler());

	return NULL;
}

