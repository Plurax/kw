/*
 * mglLibraryInfo.cpp
 *
 *  Created on: 13.02.2014
 *      Author: cromas
 */


#include "mglLibraryInfo.h"

mglLibraryInfo::mglLibraryInfo(	string name, string version, string description, string author, string license)
{
	m_name = name;
	m_version = version;
	m_description = description;
	m_author = author;
	m_license = license;
}
