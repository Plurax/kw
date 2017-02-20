/*
 * kwGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWGUIACTIONFUNCTORFACTORY_H_
#define KWGUIACTIONFUNCTORFACTORY_H_

#include <kwMessageHandler.h>
#include "kwLibraryInfo.h"
#include "kwObjectFactory.h"
#include "kwValString.h"
#include <memory>

using namespace std;


class kwMessageHandlerFactory : public kwObjectFactory
{
public:
	kwMessageHandlerFactory();
	~kwMessageHandlerFactory();

	shared_ptr<kwObject> createObject(kwValString* classname, json configuration);
};


typedef kwMessageHandlerFactory* (*GuiActFctCreateFunc)();
typedef void (*GuiActDestroyFunc)(kwMessageHandlerFactory*);


#endif /* KWGUIACTIONFUNCTORFACTORY_H_ */
