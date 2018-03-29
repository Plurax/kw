/*
 * kwLibraryInfo.h
 *
 *  Created on: 13.02.2014
 *      Author: chuhlich
 */

#ifndef KWLIBRARYINFO_H_
#define KWLIBRARYINFO_H_


#include <string>
#include "kw/kwObject.h"

using namespace std;

class kwLibraryInfo : public kwObject
{
public:
	kwLibraryInfo(	string name, string version, string description, string author, string license);
	~kwLibraryInfo();
	
	string asString();
	string m_name;
	string m_version;
	string m_description;
	string m_author;
	string m_license;
};

typedef kwLibraryInfo* (*FctGetLibraryInfo)();



#endif /* KWLIBRARYINFO_H_ */
