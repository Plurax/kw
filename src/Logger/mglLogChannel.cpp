/*
 * mglLogChannel.cpp
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */


#include "mglLogChannel.h"
#include "mglLogDeviceFile.h"
#include "mglLogDeviceStdOut.h"
#include "mglLogDeviceStdErr.h"
#include <string>
#include <sstream>

using namespace std;


mglLogChannel::mglLogChannel(string name)
{
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


void mglLogChannel::setMask(unsigned short msk)
{
	m_usMask = msk;
}

unsigned short mglLogChannel::getMask()
{
	return m_usMask;
}

