/*
 * mglLogChannel.cpp
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */


#include "mglLogChannel.h"

using namespace std;

mglLogChannel::mglLogChannel(string name)
{
	m_name = name;
}

void mglLogChannel::log(stringstream& line)
{
//	cout << line.str() << "\n";
}

void mglLogChannel::addLibraryFilter(string& libraryname, unsigned short value)
{
	m_libraryFilters.insert(pair<string,unsigned short>(libraryname,value));
}


void mglLogChannel::addClassFilter(string& classname, unsigned short value)
{
	m_classFilters.insert(pair<string,unsigned short>(classname,value));
}


unsigned short mglLogChannel::getLibraryFilter(string& libraryname)
{
	return m_libraryFilters.find(libraryname)->second;
}

unsigned short mglLogChannel::getClassFilter(string& classname)
{
	return m_libraryFilters.find(classname)->second;
}
