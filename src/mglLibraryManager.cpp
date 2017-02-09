/*
 * mglObjectManager.cpp
 *
 *  Created on: 03.11.2013
 *      Author: chuhlich
 */

#include "mglLibraryManager.h"
#include "mglDebug.h"
#include "mglLibHandle.h"
#include "mglSystem.h"
#include "mglDataSourceFactory.h"
#include "mglMessageHandlerFactory.h"

using namespace std;

mglLibraryManager::~mglLibraryManager()
{
/* TODO: Deinit loaded libraries
* via dlclose and FreeLibrary
*/
}

/**! Initialize base factories for default objects
 */
void mglLibraryManager::init()
{
	// The basic handle...
	auto defaultLibHandle = make_shared<mglLibHandle>(nullptr,
													  mglSystem::Inst().m_libInfo);

	// Note this is not a shared_ptr because this is also used for init of external factories!
	mglObjectFactory* defaultObjFactory = new mglDataSourceFactory();

	auto main_class = make_shared<mglValString>("mglDataSource");
	defaultLibHandle->addFactory(defaultObjFactory, main_class);

	m_loadedLibraries.insert(std::pair<mglValString,shared_ptr<mglLibHandle>>(
								   mglValString("mgl"),
								   defaultLibHandle));

	// Object constructors
	main_class = make_shared<mglValString>("mglMessageHandler");
	mglObjectFactory* defaultActFactory = new mglMessageHandlerFactory();
	defaultLibHandle->addFactory(defaultActFactory, main_class);
}



/**!
 * Create an object
 * The function creates an object of the given class from the given libname.
 * @param libname the library to choose from
 * @param classname the class to instantiate
 * @param main_classname this is the intentional class type to create. It is necessary to create libraries which provide different 
 * classes.
 */
shared_ptr<mglObject> mglLibraryManager::createObject(shared_ptr<mglValString> libname, shared_ptr<mglValString> classname, shared_ptr<mglValString> main_classname, json configuration)
{
	// Found the requested library in the map?
	std::map<mglValString,shared_ptr<mglLibHandle>>::iterator libIterator = m_loadedLibraries.find(*libname);

	/* The sub_class is necessary to create a custom name for the getter function of the factory.
	 * This is necessary to allow providing different classes from the same library and making lib loading independend...
	 */
	auto getprefix = mglValString("get");
	auto getsuffix = mglValString("Factory");
	auto s_Requestfunction = getprefix + *main_classname + getsuffix;
	
	mglObjectFactory* factory = nullptr;

	if (libIterator != m_loadedLibraries.end())
	{
		factory  = libIterator->second->getFactory(main_classname);
	}

	if (factory)
	{
		shared_ptr<mglObject> retObject = factory->createObject(classname.get(), configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglObject of type " << *classname);
	}

	// otherwise load lib and retrive factory...

	{
	  LOG_DEBUG << "Loading library: " << *libname;
#ifdef WIN32
		WCHAR ConvString[200];
		MultiByteToWideChar(CP_UTF8, 0, libname->str()->c_str(), -1, ConvString, 200);
		HINSTANCE handle = LoadLibrary(ConvString);
#else
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY | RTLD_GLOBAL);
#endif

		if (!handle)
		{
			std::cerr << "LibraryManager: Cannot open library: ";
#ifndef WIN32
			std::cerr << dlerror();
#endif
			std::cerr << '\n';
			THROW_TECHNICAL_EXCEPTION(666, "Could not load library " << *libname);
		}
		
		LOG_DEBUG << "Loaded...";

#ifdef WIN32
		FctCreateFunc getfactoryfct = (FctCreateFunc)GetProcAddress(handle, s_Requestfunction.str()->c_str());
		FctGetLibraryInfo getLibraryInfo = (FctGetLibraryInfo) GetProcAddress(handle, "getLibraryInfo");
#else
		FctCreateFunc getfactoryfct = (FctCreateFunc)dlsym(handle, s_Requestfunction.str()->c_str()); //"get<CLASSNAME>Factory"
		FctGetLibraryInfo getLibraryInfo = (FctGetLibraryInfo)dlsym(handle, "getLibraryInfo"); //"getLibraryInfo"
#endif
		if (nullptr == getfactoryfct)
		{
			THROW_TECHNICAL_EXCEPTION(666, "Procadress retrieval for " << s_Requestfunction << " failed!");
		}

		mglObjectFactory* factory = getfactoryfct();

		if (!factory)
		{
			THROW_TECHNICAL_EXCEPTION(666, "Factory for " << *main_classname << " could not be created!");
		}

		auto libinfo = getLibraryInfo();
		auto LibHandle = make_shared<mglLibHandle>(handle, libinfo);

		// Add the factory into the typed map for future use
		LibHandle->addFactory(factory, *main_classname);

		LOG_DEBUG << "Loaded Object library: " << libinfo->asString();

		m_loadedLibraries.insert(std::pair<mglValString, shared_ptr<mglLibHandle>>(*libname,LibHandle));

		shared_ptr<mglObject> retObject = factory->createObject(classname.get(), configuration);
		if (retObject)
			return retObject;
		else
			THROW_TECHNICAL_EXCEPTION(1, "Error during instantiation of mglObject " << *classname);
	}
	return nullptr;
}
