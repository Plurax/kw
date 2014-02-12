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
#include <set>

using namespace std;

class mglLogChannel
{
public:
	void addLibraryFilter(string& libraryname, unsigned short value);
	void addClassFilter(string& classname, unsigned short value);

	unsigned short getLibraryFilter(const char* libraryname);
	unsigned short getClassFilter(const char* classname);

	void log(stringstream& line);
	mglLogChannel(string name);

	void setMask(unsigned short msk);
	unsigned short getMask();

	bool classesEmpty();
	bool librariesEmpty();


private:
	mglLogDevice* m_logDevice;

	unsigned short m_usMask;

	map<string,unsigned short> m_libraryFilters;
	map<string,unsigned short> m_classFilters;

	bool m_classesEmpty, m_librariesEmpty;

	set<string> m_classes; // If this is empty - all classes will log
	set<string> m_libraries;// If this is empty - all classes will log
};

#endif /* MGLLOGCHANNEL_H_ */
