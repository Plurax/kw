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
#include "mglValues/mglValString.h"
#include <memory>

using namespace std;


class mglMessageHandlerFactory
{
public:
	virtual ~mglMessageHandlerFactory();
	virtual mglLibraryInfo* getLibInfo();
	virtual shared_ptr<mglMessageHandler> createMessageHandler(mglValString* classname);
};


typedef mglMessageHandlerFactory* (*GuiActFctCreateFunc)();
typedef void (*GuiActDestroyFunc)(mglMessageHandlerFactory*);


#endif /* MGLGUIACTIONFUNCTORFACTORY_H_ */
