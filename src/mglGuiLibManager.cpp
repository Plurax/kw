/*
 * mglObjectManager.cpp
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#include "../include/mglGuiLibManager.h"
#include "../include/mglGuiObjectFactory.h"
#include "mglLogger/mglLogger.h"

using namespace std;

mglGuiLibManager::~mglGuiLibManager()
{

}

void mglGuiLibManager::init()
{
	mglGuiObjectFactory* defaultObjFactory = new mglGuiObjectFactory();
	mglGuiActionFactory* defaultActFactory = new mglGuiActionFactory();

	m_loadedGuiLibraries.insert(std::pair<string,mglGuiObjectFactory*>(string("mgl"),defaultObjFactory));
	m_loadedActionLibraries.insert(std::pair<string,mglGuiActionFactory*>(string("mgl"),defaultActFactory));
}

mglGuiObject* mglGuiLibManager::createGUIObject(string* libname, string* classname, DOMElement* configuration)
{

	// Found the requested library in the map?
	std::map<string,mglGuiObjectFactory*>::iterator libIterator = m_loadedGuiLibraries.find(*libname);

	if (libIterator != m_loadedGuiLibraries.end())
	{
		return libIterator->second->createGuiObject(classname, configuration);
	}
	else
	{
		void* handle = dlopen(libname->c_str(), RTLD_LAZY);

		if (!handle)
		{
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			// TODO: Throw exception
		}

		GuiFctCreateFunc getfactoryfct = (GuiFctCreateFunc) dlsym(handle, "getFactory");
		mglGuiObjectFactory* factory = getfactoryfct();
		m_loadedGuiLibraries.insert(std::pair<string,mglGuiObjectFactory*>(string(libname->c_str()),factory));
		return factory->createGuiObject(classname, configuration);
	}



    return NULL;
}

mglGuiActionFunctor* mglGuiLibManager::createGuiAction(string* libname, string* classname)
{
	// Found the requested library in the map?
	std::map<string,mglGuiActionFactory*>::iterator libIterator = m_loadedActionLibraries.find(*libname);

	if (libIterator != m_loadedActionLibraries.end())
	{
		return libIterator->second->createGuiAction(classname);
	}
	else
	{
		void* handle = dlopen(libname->c_str(), RTLD_LAZY);

		if (!handle)
		{
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			// TODO: Throw exception
		}

		GuiActFctCreateFunc getfactoryfct = (GuiActFctCreateFunc) dlsym(handle, "getGuiActFactory");
		mglGuiActionFactory* factory = getfactoryfct();
		m_loadedActionLibraries.insert(std::pair<string,mglGuiActionFactory*>(string(libname->c_str()),factory));
		return factory->createGuiAction(classname);
	}

    return NULL;
}
