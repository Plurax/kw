/*
 * mglGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLGUIACTIONFUNCTORFACTORY_H_
#define MGLGUIACTIONFUNCTORFACTORY_H_

#include "mglGui/mglGuiActionFunctor.h"
#include <string>
#include <memory>

using namespace std;


class mglGuiActionFactory
{
public:
	virtual ~mglGuiActionFactory() {};

	virtual mglGuiActionFunctor* createGuiAction(string* classname);
};


typedef mglGuiActionFactory* (*GuiActFctCreateFunc)();
typedef void (*GuiActDestroyFunc)(mglGuiActionFactory*);


#endif /* MGLGUIACTIONFUNCTORFACTORY_H_ */
