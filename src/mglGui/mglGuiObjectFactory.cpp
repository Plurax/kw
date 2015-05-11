/*
 * mglGuiObjectFactory.cpp
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#include "mglGui/mglGuiObjectFactory.h"
#include <stdio.h>
#include "mglSystem.h"

/*
 * For the first time the standard object factory can only return mglWindow!
 */
mglGuiObject* mglGuiObjectFactory::createGuiObject(mglValString* classname, DOMElement* configuration)
{
	if (classname->str()->compare("mglGuiObject") == 0)
		return new mglGuiObject(configuration);

	return NULL;
}



mglLibraryInfo* mglGuiObjectFactory::getLibInfo()
{
	return mglSystem::Inst().m_libInfo;
}


void mglGuiObjectFactory::deleteGuiObject(mglGuiObject* _obj)
{
}

