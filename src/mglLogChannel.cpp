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
#include <stdio.h>
#include <time.h>

using namespace std;


mglLogChannel::mglLogChannel(string name)
{
	m_classesEmpty = true;
	m_librariesEmpty = true;

	if (name.compare("stdout") == 0)
	{
		m_logDevice = new mglLogDeviceStdOut();
	}
	else
		if (name.compare("stderr") == 0)
		{
			m_logDevice = new mglLogDeviceStdErr();
		}
		else
		{
			m_logDevice = new mglLogDeviceFile(name.c_str());
		}
}

/**
 * This function will create a local timestamp to be put on the start on the line.
 * The following appended line comes from the general macros used in the code.
 * @param line - stringstream line to log
 */
void mglLogChannel::log(stringstream& line)
{
	time_t now;
	struct tm * timeinfo;
	char buffer[20];
	buffer [14] = (char)0;
	buffer [15] = (char)0;
	time(&now);
	timeinfo = localtime(&now);
	strftime (buffer,15,"%Y%m%d%H%M%S",timeinfo);

	(*m_logDevice) << buffer;
	(*m_logDevice) << ":";
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

