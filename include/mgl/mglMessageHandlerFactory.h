/*
 * mglGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLGUIACTIONFUNCTORFACTORY_H_
#define MGLGUIACTIONFUNCTORFACTORY_H_

#include <mglMessageHandler.h>
#include "mglLibraryInfo.h"
#include "mglObjectFactory.h"
#include "mglValString.h"
#include <memory>

using namespace std;


class mglMessageHandlerFactory : public mglObjectFactory
{
public:
	mglMessageHandlerFactory();
	~mglMessageHandlerFactory();

	shared_ptr<mglObject> createObject(mglValString* classname, json configuration);
};


typedef mglMessageHandlerFactory* (*GuiActFctCreateFunc)();
typedef void (*GuiActDestroyFunc)(mglMessageHandlerFactory*);


#endif /* MGLGUIACTIONFUNCTORFACTORY_H_ */
