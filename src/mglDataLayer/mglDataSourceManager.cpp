/*
 * mglDataSourceManager.cpp
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */




#include "mglReleaseInfo.h"
#include "mglDataLayer/mglDataSourceManager.h"
#include "mglDataLayer/mglDataSourceFactory.h"
#include "mglDebug/mglDebug.h"
#include "mglDataLayer/mglDataLibHandle.h"
#include "mglSystem.h"

using namespace std;

mglDataSourceManager::~mglDataSourceManager()
{
}

void mglDataSourceManager::init()
{
	// Note this is not a shared_ptr because this is also used for init of external factories!
	auto defaultObjFactory = new mglDataSourceFactory();
	auto defaultDataSourceLibHandle = shared_ptr<mglDataLibHandle>(new mglDataLibHandle(NULL,
																						mglSystem::Inst().m_libInfo,
																						defaultObjFactory));

	m_loadedDataSources.insert(std::pair<mglValString,shared_ptr<mglDataLibHandle>>(
								   mglValString("mgl"),
								   defaultDataSourceLibHandle));
}

shared_ptr<mglDataSource> mglDataSourceManager::createDataSource(shared_ptr<mglValString>& libname, shared_ptr<mglValString>& classname, json configuration)
{

	// Found the requested library in the map?
	std::map<mglValString,shared_ptr<mglDataLibHandle>>::iterator libIterator = m_loadedDataSources.find(*libname);

	if (libIterator != m_loadedDataSources.end())
	{
		return libIterator->second->m_factory->createDataSource(classname.get(), configuration);
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
			std::cerr << "DataSourceManager: Cannot open library: ";
#ifndef WIN32
			std::cerr << dlerror();
#endif
			std::cerr << '\n';
			// TODO: Throw exception
		}

#ifdef WIN32
		DataSourceCreateFunc getfactoryfct = (DataSourceCreateFunc) GetProcAddress(handle, "getFactory");
		LibInfoRetrieveFunc getLibInfofct = (LibInfoRetrieveFunc) GetProcAddress(handle, "getLibInfo");
#else
		DataSourceCreateFunc getfactoryfct = (DataSourceCreateFunc) dlsym(handle, "getFactory");
		LibInfoRetrieveFunc getLibInfofct = (LibInfoRetrieveFunc) dlsym(handle, "getLibInfo");
#endif
		mglDataSourceFactory* factory = getfactoryfct();
		auto thisInfo = getLibInfofct();
		auto DataSourceLibHandle = shared_ptr<mglDataLibHandle>(new mglDataLibHandle(handle, thisInfo, factory));

		m_loadedDataSources.insert(std::pair<mglValString,shared_ptr<mglDataLibHandle>>(*libname,DataSourceLibHandle ));
		return factory->createDataSource(classname.get(), configuration);
	}
    return NULL;
}
