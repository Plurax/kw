/*
 * mglGuiActionFunctorFactory.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "mglGui/mglGuiActionFactory.h"
#include <stdio.h>
#include "mglSystem.h"

/*
 * For the first time the standard object factory can only return mglWindow!
 */
mglGuiActionFunctor* mglGuiActionFactory::createGuiAction(string* classname)
{
	if (classname->compare("mglGuiAction") == 0)
		return new mglGuiActionFunctor();

	return NULL;
}


mglLibraryInfo* mglGuiActionFactory::getLibInfo()
{
	return mglSystem::Inst().m_libInfo;
}


mglGuiActionFactory::~mglGuiActionFactory()
{}
