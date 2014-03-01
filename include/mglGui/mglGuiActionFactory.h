/*
 * mglGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLGUIACTIONFUNCTORFACTORY_H_
#define MGLGUIACTIONFUNCTORFACTORY_H_

#include "mglGui/mglGuiActionFunctor.h"
#include "mglLibraryInfo.h"
#include "mglValues/mglValString.h"
#include <memory>

using namespace std;


class mglGuiActionFactory
{
public:
	virtual ~mglGuiActionFactory();
	virtual mglLibraryInfo* getLibInfo();
	virtual mglGuiActionFunctor* createGuiAction(mglValString* classname);
};


typedef mglGuiActionFactory* (*GuiActFctCreateFunc)();
typedef void (*GuiActDestroyFunc)(mglGuiActionFactory*);


#endif /* MGLGUIACTIONFUNCTORFACTORY_H_ */
