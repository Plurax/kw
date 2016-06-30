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
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

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

	auto defaultGuiLibHandle = make_shared<mglGuiLibHandle>(nullptr,
															mglSystem::Inst().m_libInfo, defaultObjFactory);

	auto defaultGuiActionLibHandle = make_shared<mglMessageHandlerLibHandle>(nullptr,
																			  mglSystem::Inst().m_libInfo, defaultActFactory);

	m_loadedGuiLibraries.insert(std::pair<mglValString, shared_ptr<mglGuiLibHandle>>(mglValString("mgl"),defaultGuiLibHandle));
	m_loadedMessageHandlerLibraries.insert(std::pair<mglValString, shared_ptr<mglMessageHandlerLibHandle>>(mglValString("mgl"),defaultGuiActionLibHandle));
}

shared_ptr<mglGuiObject> mglGuiLibManager::createGUIObject(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname, json configuration)
{
	INIT_LOG("mglGuiLibManager", "createGUIObject(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname, json configuration)");

	// Found the requested library in the map?
	std::map<mglValString,shared_ptr<mglGuiLibHandle>>::iterator libIterator = m_loadedGuiLibraries.find(*libname);

	if (libIterator != m_loadedGuiLibraries.end())
	{
		shared_ptr<mglGuiObject> retObject = libIterator->second->m_factory->createGuiObject(classname.get(), configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglGuiObject of type " << *classname);
	}
	else
	{
		LOG_DEBUG("Loading library: " << *libname);
#ifdef WIN32
		WCHAR ConvString[200];
		MultiByteToWideChar(CP_UTF8, 0, libname->str()->c_str(), -1, ConvString, 200);
		HINSTANCE handle = LoadLibrary(ConvString);
#else
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY | RTLD_GLOBAL);
#endif

		if (!handle)
		{
			std::cerr << "GUILibManager: Cannot open library: ";
#ifndef WIN32
			std::cerr << dlerror();
#endif
			std::cerr << '\n';
			THROW_TECHNICAL_EXCEPTION(666, "Could not load library " << *libname);
		}

#ifdef WIN32
		GuiFctCreateFunc getfactoryfct = (GuiFctCreateFunc)GetProcAddress(handle, "getGuiObjectFactory");
#else
		GuiFctCreateFunc getfactoryfct = (GuiFctCreateFunc)dlsym(handle, "getGuiObjectFactory");
#endif
		mglGuiObjectFactory* factory = getfactoryfct();

		auto GuiLibHandle = make_shared<mglGuiLibHandle>(handle, factory->getLibInfo(), factory);

		LOG_DEBUG("Loaded GuiObject library: " << GuiLibHandle->getInfo()->asString());

		m_loadedGuiLibraries.insert(std::pair<mglValString, shared_ptr<mglGuiLibHandle>>(*libname,GuiLibHandle));

		shared_ptr<mglGuiObject> retObject = factory->createGuiObject(classname.get(), configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglGuiObject " << *classname);
	}
}

shared_ptr<mglMessageHandler> mglGuiLibManager::createMessageHandler(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname)
{
	INIT_LOG("mglGuiLibManager", "createGuiAction(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname)");
	// Found the requested library in the map?
	std::map<mglValString, shared_ptr<mglMessageHandlerLibHandle>>::iterator libIterator = m_loadedMessageHandlerLibraries.find(*libname);

	if (libIterator != m_loadedMessageHandlerLibraries.end())
	{
		return libIterator->second->m_factory->createMessageHandler(classname.get());
	}
	else
	{
#ifdef WIN32
		WCHAR ConvString[200];
		MultiByteToWideChar(CP_UTF8, 0, libname->str()->c_str(), -1, ConvString, 200);
		HINSTANCE handle = LoadLibrary(ConvString);
#else
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY | RTLD_GLOBAL);
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
		GuiActFctCreateFunc getfactoryfct = (GuiActFctCreateFunc) GetProcAddress(handle, "getMessageHandlerFactory");
#else
		GuiActFctCreateFunc getfactoryfct = (GuiActFctCreateFunc)dlsym(handle, "getMessageHandlerFactory");
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

		shared_ptr<mglMessageHandlerLibHandle> GuiActionLibHandle = shared_ptr<mglMessageHandlerLibHandle>(new mglMessageHandlerLibHandle(handle, factory->getLibInfo(), factory));

		LOG_DEBUG("Loaded GuiAction library: " << GuiActionLibHandle->getInfo()->asString());

		m_loadedMessageHandlerLibraries.insert(std::pair<mglValString, shared_ptr<mglMessageHandlerLibHandle>>(*libname,GuiActionLibHandle));
		
		shared_ptr<mglMessageHandler> retObject = factory->createMessageHandler(classname.get());
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglMessageHandler " << *classname);
	}

    return NULL;
}
