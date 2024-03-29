/*
 * kwLibraryInfo.cpp
 *
 *  Created on: 13.02.2014
 *      Author: chuhlich
 */


#include "kwLibraryInfo.h"

kwLibraryInfo::~kwLibraryInfo()
{
}

kwLibraryInfo::kwLibraryInfo(	string name, string version, string description, string author, string license)
{
	m_name = name;
	m_version = version;
	m_description = description;
	m_author = author;
	m_license = license;
}


string kwLibraryInfo::asString()
{
	string ret = "Libname: " + m_name + "\nVersion: " + m_version
			+ "\nDescription: " + m_description + "\nAuthor: " + m_author + "\nLicense: " + m_license;
	return ret;
}
