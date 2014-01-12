/*
 * mglLogChannel.h
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#ifndef MGLLOGCHANNEL_H_
#define MGLLOGCHANNEL_H_

#include <iostream>
#include <fstream>
#include "mglLogDevice.h"
#include <map>

using namespace std;

class mglLogChannel
{
public:
	void addLibraryFilter(string& libraryname, unsigned short value);
	void addClassFilter(string& classname, unsigned short value);
	void addClass(string& _classname);
	void addLibrary(string& _libraryname);

	unsigned short getLibraryFilter(string& libraryname);
	unsigned short getClassFilter(string& classname);

	void log(stringstream& line);
	mglLogChannel(string name);

	void setMask(unsigned short msk);
	unsigned short getMask();

private:
	mglLogDevice* m_logDevice;

	unsigned short m_usMask;

	map<string,unsigned short> m_libraryFilters;
	map<string,unsigned short> m_classFilters;
	map<string, string> m_classes; // If this is empty - all classes will log
	map<string, string> m_libraries;// If this is empty - all classes will log
};

#endif /* MGLLOGCHANNEL_H_ */
