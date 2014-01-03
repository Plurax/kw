/*
 * mglGuiActionFunctorFactory.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "../include/mglGuiActionFactory.h"
#include <stdio.h>


/*
 * For the first time the standard object factory can only return mglWindow!
 */
mglGuiActionFunctor* mglGuiActionFactory::createGuiAction(string* classname)
{
	if (classname->compare("mglGuiAction") == 0)
		return new mglGuiActionFunctor();

	return NULL;
}
