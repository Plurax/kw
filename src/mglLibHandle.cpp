/*
 * mglLibHandle.cpp
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#include "mglLibHandle.h"

mglLibHandle::mglLibHandle(void* handle, std::string name, std::string version, std::string libraryname)
{
	m_name = name;
	m_version = version;
	m_libraryName = libraryname;
}

mglLibHandle::~mglLibHandle()
{

}

std::string mglLibHandle::getName()
{
	return m_name;
}

std::string mglLibHandle::getLibraryName()
{
	return m_libraryName;
}


std::string mglLibHandle::getVersion()
{
	return m_version;
}


