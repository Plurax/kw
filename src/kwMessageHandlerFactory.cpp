/*
 * kwMessageHandlerFactory.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#include <kwMessageHandlerFactory.h>
#include <stdio.h>
#include "kwSystem.h"
#include "kwTestHandler.h"



kwMessageHandlerFactory::kwMessageHandlerFactory()
{
}

kwMessageHandlerFactory::~kwMessageHandlerFactory()
{
}

/*
 * For the first time the standard object factory can only return kwTestHandler!
 */
shared_ptr<kwObject> kwMessageHandlerFactory::createObject(kwValString* classname, json configuration)
{
  shared_ptr<kwObject> ret = nullptr;
  if (*classname == kwValString("kwTestHandler"))
    ret = make_shared<kwTestHandler>();

  return ret;
}

