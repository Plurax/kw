/*
 * kwGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWMESSAGEHANDLERFACTORY_H_
#define KWMESSAGEHANDLERFACTORY_H_

#include <kw/kwMessageHandler.h>
#include "kw/kwLibraryInfo.h"
#include "kw/kwObjectFactory.h"
#include "kw/kwValString.h"
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


#endif /* KWMESSAGEHANDLERFACTORY_H_ */
