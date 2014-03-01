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
		void* handle = dlopen(libname->str()->c_str(), RTLD_LAZY);

		if (!handle)
		{
			std::cerr << "DataSourceManager: Cannot open library: " << dlerror() << '\n';
			// TODO: Throw exception
		}

		DataSourceCreateFunc getfactoryfct = (DataSourceCreateFunc) dlsym(handle, "getFactory");
		LibInfoRetrieveFunc getLibInfofct = (LibInfoRetrieveFunc) dlsym(handle, "getLibInfo");
		mglDataSourceFactory* factory = getfactoryfct();
		mglLibraryInfo* thisInfo = getLibInfofct();
		mglDataLibHandle* DataSourceLibHandle = new mglDataLibHandle(handle, thisInfo, factory);

		m_loadedDataSources.insert(std::pair<mglValString,mglDataLibHandle*>(*libname,DataSourceLibHandle ));
		return factory->createDataSource(classname, configuration);
	}
    return NULL;
}
