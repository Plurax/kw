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
	mglMessageHandlerFactory* defaultActFactory = new mglMessageHandlerFactory();

	mglGuiLibHandle* defaultGuiLibHandle = new mglGuiLibHandle(NULL,
			mglSystem::Inst().m_libInfo, defaultObjFactory);

	mglMessageHandlerLibHandle* defaultGuiActionLibHandle = new mglMessageHandlerLibHandle(NULL,
			mglSystem::Inst().m_libInfo, defaultActFactory);


	m_loadedGuiLibraries.insert(std::pair<mglValString,mglGuiLibHandle*>(mglValString("mgl"),defaultGuiLibHandle));
	m_loadedMessageHandlerLibraries.insert(std::pair<mglValString,mglMessageHandlerLibHandle*>(mglValString("mgl"),defaultGuiActionLibHandle));
}

mglGuiObject* mglGuiLibManager::createGUIObject(mglValString* libname, mglValString* classname, DOMElement* configuration)
{
	INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
	// Found the requested library in the map?
	std::map<mglValString,mglGuiLibHandle*>::iterator libIterator = m_loadedGuiLibraries.find(*libname);

	mglGuiObject* retObject = NULL;

	if (libIterator != m_loadedGuiLibraries.end())
	{
		retObject = libIterator->second->m_factory->createGuiObject(classname, configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglGuiObject " << *classname);
	}
	else
	{
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY);

		if (!handle)
		{
			std::cerr << "GUILibManager: Cannot open library: " << dlerror() << '\n';
			INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
			THROW_TECHNICAL_EXCEPTION(666, "Could not load library " << *libname);
		}


		GuiFctCreateFunc getfactoryfct = (GuiFctCreateFunc) dlsym(handle, "getFactory");
		mglGuiObjectFactory* factory = getfactoryfct();

		mglGuiLibHandle* GuiLibHandle = new mglGuiLibHandle(handle, factory->getLibInfo(), factory);

		INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
		LOG_DEBUG("Loaded GuiObject library: " << GuiLibHandle->getInfo()->asString());

		m_loadedGuiLibraries.insert(std::pair<mglValString,mglGuiLibHandle*>(*libname,GuiLibHandle));

		retObject = factory->createGuiObject(classname, configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglGuiObject " << *classname);
	}
}

mglMessageHandler* mglGuiLibManager::createMessageHandler(mglValString* libname, mglValString* classname)
{
	INIT_LOG("mglGuiLibManager", "createGuiAction(string* libname, string* classname)");
	// Found the requested library in the map?
	std::map<mglValString,mglMessageHandlerLibHandle*>::iterator libIterator = m_loadedMessageHandlerLibraries.find(*libname);

	if (libIterator != m_loadedMessageHandlerLibraries.end())
	{
		return libIterator->second->m_factory->createMessageHandler(classname);
	}
	else
	{
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY);

		if (!handle)
		{
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			// TODO: Throw exception
		}

		GuiActFctCreateFunc getfactoryfct = (GuiActFctCreateFunc) dlsym(handle, "getGuiActFactory");
		mglMessageHandlerFactory* factory = getfactoryfct();
		if (factory == NULL)
			THROW_TECHNICAL_EXCEPTION(666, dlerror());

		mglMessageHandlerLibHandle* GuiActionLibHandle = new mglMessageHandlerLibHandle(handle, factory->getLibInfo(), factory);

		INIT_LOG("mglGuiLibManager", "createGUIObject(mglValString* libname, mglValString* classname, DOMElement* configuration)");
		LOG_DEBUG("Loaded GuiAction library: " << GuiActionLibHandle->getInfo()->asString());

		m_loadedMessageHandlerLibraries.insert(std::pair<mglValString,mglMessageHandlerLibHandle*>(*libname,GuiActionLibHandle));
		return factory->createMessageHandler(classname);
	}

    return NULL;
}
