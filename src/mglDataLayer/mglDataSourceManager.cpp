/*
 * mglDataSourceManager.cpp
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */





#include "mglDataLayer/mglDataSourceManager.h"
#include "mglDataLayer/mglDataSourceFactory.h"
#include "mglDebug/mglLogger.h"

using namespace std;

mglDataSourceManager::~mglDataSourceManager()
{

}

void mglDataSourceManager::init()
{
	mglDataSourceFactory* defaultObjFactory = new mglDataSourceFactory();

	m_loadedDataSources.insert(std::pair<string,mglDataSourceFactory*>(string("mgl"),defaultObjFactory));
}

mglDataSource* mglDataSourceManager::createDataSource(string* libname, string* classname, DOMElement* configuration)
{

	// Found the requested library in the map?
	std::map<string,mglDataSourceFactory*>::iterator libIterator = m_loadedDataSources.find(*libname);

	if (libIterator != m_loadedDataSources.end())
	{
		return libIterator->second->createDataSource(classname, configuration);
	}
	else
	{
		void* handle = dlopen(libname->c_str(), RTLD_LAZY);

		if (!handle)
		{
			std::cerr << "Cannot open library: " << dlerror() << '\n';
			// TODO: Throw exception
		}

		DataSourceCreateFunc getfactoryfct = (DataSourceCreateFunc) dlsym(handle, "getFactory");
		mglDataSourceFactory* factory = getfactoryfct();
		m_loadedDataSources.insert(std::pair<string,mglDataSourceFactory*>(string(libname->c_str()),factory));
		return factory->createDataSource(classname, configuration);
	}
    return NULL;
}
