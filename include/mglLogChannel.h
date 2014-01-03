/*
 * mglLogChannel.h
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#ifndef MGLLOGCHANNEL_H_
#define MGLLOGCHANNEL_H_

#include <iostream>
#include <map>

using namespace std;

class mglLogChannel
{
	mglLogChannel(string name);

	string m_name;

	map<string,unsigned short> m_libraryFilters;
	map<string,unsigned short> m_classFilters;

	void addLibraryFilter(string& libraryname, unsigned short value);
	void addClassFilter(string& classname, unsigned short value);

	unsigned short getLibraryFilter(string& libraryname);
	unsigned short getClassFilter(string& classname);

	void log(stringstream& line);
};

#endif /* MGLLOGCHANNEL_H_ */
