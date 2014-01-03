/*
 * mglLibHandle.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#ifndef MGLLIBHANDLE_H_
#define MGLLIBHANDLE_H_

#include <string>

class mglLibHandle
{
public:
	mglLibHandle(void* handle, std::string name, std::string version, std::string libraryname);
	~mglLibHandle();

	std::string getName();
	std::string getLibraryName();
	std::string getVersion();
private:
	std::string m_name;
	std::string m_libraryName;
	std::string m_version;


};

#endif /* MGLLIBHANDLE_H_ */
