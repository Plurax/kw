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
	mglDataSourceFactory* defaultObjFactory = new mglDataSourceFactory();
	mglDataLibHandle* defaultDataSourceLibHandle = new mglDataLibHandle(NULL,
			mglSystem::Inst().m_libInfo,
			defaultObjFactory);

	m_loadedDataSources.insert(std::pair<mglValString,mglDataLibHandle*>(mglValString("mgl"),defaultDataSourceLibHandle));
}

mglDataSource* mglDataSourceManager::createDataSource(mglValString* libname, mglValString* classname, DOMElement* configuration)
{

	// Found the requested library in the map?
	std::map<mglValString,mglDataLibHandle*>::iterator libIterator = m_loadedDataSources.find(*libname);

	if (libIterator != m_loadedDataSources.end())
	{
		return libIterator->second->m_factory->createDataSource(classname, configuration);
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
		mglLibraryInfo* thisInfo = getLibInfofct();
		mglDataLibHandle* DataSourceLibHandle = new mglDataLibHandle(handle, thisInfo, factory);

		m_loadedDataSources.insert(std::pair<mglValString,mglDataLibHandle*>(*libname,DataSourceLibHandle ));
		return factory->createDataSource(classname, configuration);
	}
    return NULL;
}
