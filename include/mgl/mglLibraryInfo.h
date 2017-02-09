/*
 * mglLibraryInfo.h
 *
 *  Created on: 13.02.2014
 *      Author: chuhlich
 */

#ifndef MGLLIBRARYINFO_H_
#define MGLLIBRARYINFO_H_


#include <string>
#include "mglObject.h"

using namespace std;

class mglLibraryInfo : public mglObject
{
public:
	mglLibraryInfo(	string name, string version, string description, string author, string license);
	~mglLibraryInfo();
	
	string asString();
	string m_name;
	string m_version;
	string m_description;
	string m_author;
	string m_license;
};

typedef mglLibraryInfo* (*FctGetLibraryInfo)();



#endif /* MGLLIBRARYINFO_H_ */
