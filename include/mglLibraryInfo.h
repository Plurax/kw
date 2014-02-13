/*
 * mglLibraryInfo.h
 *
 *  Created on: 13.02.2014
 *      Author: cromas
 */

#ifndef MGLLIBRARYINFO_H_
#define MGLLIBRARYINFO_H_


#include <string>

using namespace std;

class mglLibraryInfo
{
public:
	mglLibraryInfo(	string name, string version, string description, string author, string license);
	string m_name;
	string m_version;
	string m_description;
	string m_author;
	string m_license;
};



#endif /* MGLLIBRARYINFO_H_ */
