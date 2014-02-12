/*
 * mglLogChannel.cpp
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */


#include "mglDebug/mglLogChannel.h"
#include "mglDebug/mglLogDeviceFile.h"
#include "mglDebug/mglLogDeviceStdOut.h"
#include "mglDebug/mglLogDeviceStdErr.h"
#include <string>
#include <sstream>

using namespace std;


mglLogChannel::mglLogChannel(string name)
{
	m_classesEmpty = true;
	m_librariesEmpty = true;

	if (name.compare(string("stdout")) == 0)
	{
		m_logDevice = new mglLogDeviceStdOut();
	}
	else
		if (name.compare(string("stderr")) == 0)
		{
			m_logDevice = new mglLogDeviceStdErr();
		}
		else
		{
			m_logDevice = new mglLogDeviceFile(name.c_str());
		}
}


void mglLogChannel::log(stringstream& line)
{
	(*m_logDevice) << line.str();
	(*m_logDevice) << "\n";
	m_logDevice->flush();
}

void mglLogChannel::addLibraryFilter(string& libraryname, unsigned short value)
{
	m_libraryFilters.insert(pair<string,unsigned short>(libraryname,value));
}


void mglLogChannel::addClassFilter(string& classname, unsigned short value)
{
	m_classFilters.insert(pair<string,unsigned short>(classname,value));
}


unsigned short mglLogChannel::getLibraryFilter(const char* libraryname)
{
	string key = string(libraryname);
	if (m_libraryFilters.size() > 0)
	{
		map<string,unsigned short>::iterator it = m_libraryFilters.find(key);
		if (it == m_libraryFilters.end())
			return (unsigned short)0x0;
		else
			return it->second;
	}
	else
		return (unsigned short)0xFFFF;
}

unsigned short mglLogChannel::getClassFilter(const char* classname)
{
	string key = string(classname);
	if (m_classFilters.size() > 0)
	{
		map<string,unsigned short>::iterator it = m_classFilters.find(key);
		if (it == m_classFilters.end())
			return (unsigned short)0x0;
		else
			return it->second;
	}
	else
		return (unsigned short)0xFFFF;
}


void mglLogChannel::setMask(unsigned short msk)
{
	m_usMask = msk;
}

unsigned short mglLogChannel::getMask()
{
	return m_usMask;
}

bool mglLogChannel::classesEmpty()
{
	return m_classesEmpty;
}

bool mglLogChannel::librariesEmpty()
{
	return m_librariesEmpty;
}

