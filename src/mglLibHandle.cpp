/*
 * mglLibHandle.cpp
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#include "mglLibHandle.h"

mglLibHandle::mglLibHandle(void* handle, mglLibraryInfo* libinfo)
{
	m_LibraryInfo = libinfo;
}

mglLibHandle::~mglLibHandle()
{

}


mglLibraryInfo* mglLibHandle::getInfo()
{
	return m_LibraryInfo;
}


void mglLibHandle::addFactory(mglObjectFactory* factory, mglValString type)
{
	m_ObjectFactories.insert(std::pair<mglValString, mglObjectFactory*>(
								   type,
								   factory));
}


mglObjectFactory* mglLibHandle::getFactory(mglValString type)
{
	std::map<mglValString, mglObjectFactory*>::iterator factoryIterator = m_ObjectFactories.find(type);
	
	mglObjectFactory* factory = nullptr;

	if (factoryIterator != m_ObjectFactories.end())
	{
		factory  = factoryIterator->second;
	}

	return factory;
}
