/*
 * kwLibHandle.cpp
 *
 *  Created on: 12.10.2013
 *      Author: chuhlich
 */

#include "kwLibHandle.h"

kwLibHandle::kwLibHandle(void* handle, kwLibraryInfo* libinfo)
{
	m_LibraryInfo = libinfo;
}

kwLibHandle::~kwLibHandle()
{

}


kwLibraryInfo* kwLibHandle::getInfo()
{
	return m_LibraryInfo;
}


void kwLibHandle::addFactory(kwObjectFactory* factory, kwValString type)
{
	m_ObjectFactories.insert(std::pair<kwValString, kwObjectFactory*>(
								   type,
								   factory));
}


kwObjectFactory* kwLibHandle::getFactory(kwValString type)
{
	std::map<kwValString, kwObjectFactory*>::iterator factoryIterator = m_ObjectFactories.find(type);
	
	kwObjectFactory* factory = nullptr;

	if (factoryIterator != m_ObjectFactories.end())
	{
		factory  = factoryIterator->second;
	}

	return factory;
}
