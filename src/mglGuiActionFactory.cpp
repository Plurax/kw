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
mglActionFunctor* mglGuiActionFactory::createGuiAction(mglValString* classname)
{
	if (classname->str()->compare("mglGuiAction") == 0)
		return new mglActionFunctor();

	return NULL;
}


mglLibraryInfo* mglGuiActionFactory::getLibInfo()
{
	return mglSystem::Inst().m_libInfo;
}


mglGuiActionFactory::~mglGuiActionFactory()
{}
