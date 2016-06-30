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
shared_ptr<mglGuiObject> mglGuiObjectFactory::createGuiObject(mglValString* classname, json configuration)
{
	if (classname->str()->compare("mglGuiObject") == 0)
		return make_shared<mglGuiObject>(configuration);
	
	return nullptr;
}



mglLibraryInfo* mglGuiObjectFactory::getLibInfo()
{
	return mglSystem::Inst().m_libInfo;
}


void mglGuiObjectFactory::deleteGuiObject(mglGuiObject* _obj)
{
}

