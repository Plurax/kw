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
/* TODO: Deinit loaded libraries
* via dlclose and FreeLibrary
*/
}

void mglGuiLibManager::init()
{
	mglGuiObjectFactory* defaultObjFactory = new mglGuiObjectFactory();
	mglMessageHandlerFactory* defaultActFactory = new mglMessageHandlerFactory();

	auto defaultGuiLibHandle = shared_ptr<mglGuiLibHandle>(new mglGuiLibHandle(NULL,
																			   mglSystem::Inst().m_libInfo, defaultObjFactory));

	auto defaultGuiActionLibHandle = shared_ptr<mglMessageHandlerLibHandle>(new mglMessageHandlerLibHandle(NULL,
																			   mglSystem::Inst().m_libInfo, defaultActFactory));


	m_loadedGuiLibraries.insert(std::pair<mglValString, shared_ptr<mglGuiLibHandle>>(mglValString("mgl"),defaultGuiLibHandle));
	m_loadedMessageHandlerLibraries.insert(std::pair<mglValString, shared_ptr<mglMessageHandlerLibHandle>>(mglValString("mgl"),defaultGuiActionLibHandle));
}

shared_ptr<mglGuiObject> mglGuiLibManager::createGUIObject(mglValString* libname, mglValString* classname, DOMElement* configuration)
{
	INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");

	// Found the requested library in the map?
	std::map<mglValString,shared_ptr<mglGuiLibHandle>>::iterator libIterator = m_loadedGuiLibraries.find(*libname);

	if (libIterator != m_loadedGuiLibraries.end())
	{
		auto retObject = libIterator->second->m_factory->createGuiObject(classname, configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglGuiObject " << *classname);
	}
	else
	{
		LOG_DEBUG("Loading library: " << *libname);
#ifdef WIN32
		WCHAR ConvString[200];
		MultiByteToWideChar(CP_UTF8, 0, libname->str()->c_str(), -1, ConvString, 200);
		HINSTANCE handle = LoadLibrary(ConvString);
#else
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY);
#endif

		if (!handle)
		{
			std::cerr << "GUILibManager: Cannot open library: ";
#ifndef WIN32
			std::cerr << dlerror();
#endif
			std::cerr << '\n';
			INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
			THROW_TECHNICAL_EXCEPTION(666, "Could not load library " << *libname);
		}

#ifdef WIN32
		GuiFctCreateFunc getfactoryfct = (GuiFctCreateFunc)GetProcAddress(handle, "getFactory");
#else
		GuiFctCreateFunc getfactoryfct = (GuiFctCreateFunc)dlsym(handle, "getFactory");
#endif
		mglGuiObjectFactory* factory = getfactoryfct();

		auto GuiLibHandle = shared_ptr<mglGuiLibHandle>(new mglGuiLibHandle(handle, factory->getLibInfo(), factory));

		INIT_LOG("mglGuiLibManager", "createGUIObject(string* libname, string* classname, DOMElement* configuration)");
		LOG_DEBUG("Loaded GuiObject library: " << GuiLibHandle->getInfo()->asString());

		m_loadedGuiLibraries.insert(std::pair<mglValString, shared_ptr<mglGuiLibHandle>>(*libname,GuiLibHandle));

		auto retObject = factory->createGuiObject(classname, configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglGuiObject " << *classname);
	}
}

shared_ptr<mglMessageHandler> mglGuiLibManager::createMessageHandler(mglValString* libname, mglValString* classname)
{
	INIT_LOG("mglGuiLibManager", "createGuiAction(string* libname, string* classname)");
	// Found the requested library in the map?
	std::map<mglValString, shared_ptr<mglMessageHandlerLibHandle>>::iterator libIterator = m_loadedMessageHandlerLibraries.find(*libname);

	if (libIterator != m_loadedMessageHandlerLibraries.end())
	{
		return libIterator->second->m_factory->createMessageHandler(classname);
	}
	else
	{
#ifdef WIN32
		WCHAR ConvString[200];
		MultiByteToWideChar(CP_UTF8, 0, libname->str()->c_str(), -1, ConvString, 200);
		HINSTANCE handle = LoadLibrary(ConvString);
#else
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY);
#endif

		if (!handle)
		{
			std::cerr << "GUILibManager: Cannot open library: ";
#ifndef WIN32
			std::cerr << dlerror();
#endif
			std::cerr << "\n";

			// TODO: Throw exception
		}
#ifdef WIN32
		GuiActFctCreateFunc getfactoryfct = (GuiActFctCreateFunc) GetProcAddress(handle, "getGuiActFactory");
#else
		GuiActFctCreateFunc getfactoryfct = (GuiActFctCreateFunc)dlsym(handle, "getGuiActFactory");
#endif
		mglMessageHandlerFactory* factory = getfactoryfct();
		if (factory == NULL)
		{
#ifdef WIN32
			THROW_TECHNICAL_EXCEPTION(666, "Error on loading factory function.");
#else
			THROW_TECHNICAL_EXCEPTION(666, dlerror());
#endif
		}

		auto GuiActionLibHandle = shared_ptr<mglMessageHandlerLibHandle>(new mglMessageHandlerLibHandle(handle, factory->getLibInfo(), factory));

		INIT_LOG("mglGuiLibManager", "createGUIObject(mglValString* libname, mglValString* classname, DOMElement* configuration)");
		LOG_DEBUG("Loaded GuiAction library: " << GuiActionLibHandle->getInfo()->asString());

		m_loadedMessageHandlerLibraries.insert(std::pair<mglValString, shared_ptr<mglMessageHandlerLibHandle>>(*libname,GuiActionLibHandle));
		return factory->createMessageHandler(classname);
	}

    return NULL;
}
