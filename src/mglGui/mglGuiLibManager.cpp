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

	mglGuiActionLibHandle* defaultGuiActionLibHandle = new mglGuiActionLibHandle(NULL,
			mglSystem::Inst().m_libInfo, defaultActFactory);


	m_loadedGuiLibraries.insert(std::pair<string,mglGuiLibHandle*>(string("mgl"),defaultGuiLibHandle));
	m_loadedActionLibraries.insert(std::pair<string,mglGuiActionLibHandle*>(string("mgl"),defaultGuiActionLibHandle));
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
		mglGuiObjectFactory* factory = getfactoryfct();

		mglGuiLibHandle* GuiLibHandle = new mglGuiLibHandle(handle, factory->getLibInfo(), factory);

		INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
		LOG_DEBUG("Loaded GuiObject library: " << GuiLibHandle->getInfo()->asString());

		m_loadedGuiLibraries.insert(std::pair<string,mglGuiLibHandle*>(*libname,GuiLibHandle));
		return factory->createGuiObject(classname, configuration);
	}
    return NULL;
}

mglGuiActionFunctor* mglGuiLibManager::createGuiAction(string* libname, string* classname)
{
	// Found the requested library in the map?
	std::map<string,mglGuiActionLibHandle*>::iterator libIterator = m_loadedActionLibraries.find(*libname);

	if (libIterator != m_loadedActionLibraries.end())
	{
		return libIterator->second->m_factory->createGuiAction(classname);
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
		if (factory == NULL)
			THROW_TECHNICAL_EXCEPTION(666, dlerror());

		mglGuiActionLibHandle* GuiActionLibHandle = new mglGuiActionLibHandle(handle, factory->getLibInfo(), factory);

		INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
		LOG_DEBUG("Loaded GuiAction library: " << GuiActionLibHandle->getInfo()->asString());

		m_loadedActionLibraries.insert(std::pair<string,mglGuiActionLibHandle*>(string(libname->c_str()),GuiActionLibHandle));
		return factory->createGuiAction(classname);
	}

    return NULL;
}
