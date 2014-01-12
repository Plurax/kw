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

using namespace std;

class mglLogDeviceFile : public mglLogDevice
{
public:
	void flush();
	mglLogDeviceFile(const char* filename);
	~mglLogDeviceFile();
	void operator << (char* str);
	void operator << (string str);
};

#endif /* MGLLOGDEVICEFILE_H_ */
