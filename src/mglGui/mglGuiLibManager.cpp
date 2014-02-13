/*
 * mglObjectManager.cpp
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#include "mglGui/mglGuiLibManager.h"
#include "mglGui/mglGuiObjectFactory.h"
#include "mglDebug/mglDebug.h"
#include "mglSystem.h"
using namespace std;

mglGuiLibManager::~mglGuiLibManager()
{

}

void mglGuiLibManager::init()
{
	mglGuiObjectFactory* defaultObjFactory = new mglGuiObjectFactory();
	mglGuiActionFactory* defaultActFactory = new mglGuiActionFactory();

	mglGuiLibHandle* defaultGuiLibHandle = new mglGuiLibHandle(NULL,
			mglSystem::Inst().m_libInfo, defaultObjFactory);

	m_loadedGuiLibraries.insert(std::pair<string,mglGuiLibHandle*>(string("mgl"),defaultGuiLibHandle));
	m_loadedActionLibraries.insert(std::pair<string,mglGuiActionFactory*>(string("mgl"),defaultActFactory));
}

mglGuiObject* mglGuiLibManager::createGUIObject(string* libname, string* classname, DOMElement* configuration)
{
	// Found the requested library in the map?
	std::map<string,mglGuiLibHandle*>::iterator libIterator = m_loadedGuiLibraries.find(*libname);

	if (libIterator != m_loadedGuiLibraries.end())
	{
		return libIterator->second->m_factory->createGuiObject(classname, configuration);
	}
	else
	{
		void* handle = dlopen(libname->c_str(), RTLD_LAZY);

		if (!handle)
		{
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
			THROW_TECHNICAL_EXCEPTION(666, "Could not load library " << libname);
		}


		GuiFctCreateFunc getfactoryfct = (GuiFctCreateFunc) dlsym(handle, "getFactory");
		LibInfoRetrieveFunc getLibInfofct = (LibInfoRetrieveFunc) dlsym(handle, "getLibInfo");
		mglGuiObjectFactory* factory = getfactoryfct();
		mglLibraryInfo* thisInfo = getLibInfofct();
		mglGuiLibHandle* GuiLibHandle = new mglGuiLibHandle(handle, thisInfo, factory);

		m_loadedGuiLibraries.insert(std::pair<string,mglGuiLibHandle*>(*libname,GuiLibHandle));
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
		LibInfoRetrieveFunc getLibInfofct = (LibInfoRetrieveFunc) dlsym(handle, "getLibInfo");
		mglGuiActionFactory* factory = getfactoryfct();
		if (factory == NULL)
			THROW_TECHNICAL_EXCEPTION(666, dlerror());
		mglLibraryInfo* thisInfo = getLibInfofct();
		if (thisInfo == NULL)
			THROW_TECHNICAL_EXCEPTION(666, dlerror());

		m_loadedActionLibraries.insert(std::pair<string,mglGuiActionFactory*>(string(libname->c_str()),factory));
		return factory->createGuiAction(classname);
	}

    return NULL;
}
