/*
 * mglLogDeviceFile.h
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */

#ifndef MGLLOGDEVICEFILE_H_
#define MGLLOGDEVICEFILE_H_

#include "mglLogDevice.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class mglLogDeviceFile : public mglLogDevice
{

public:
	void flush();
	mglLogDeviceFile(const char* filename);
	~mglLogDeviceFile();
	void operator << (char* str);
	void operator << (const char* str);
	void operator << (string str);

private:
	ofstream m_outputFile;
};

#endif /* MGLLOGDEVICEFILE_H_ */
