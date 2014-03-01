/*
 * mglLogDeviceStdOut.h
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */

#ifndef MGLLOGDEVICESTDOUT_H_
#define MGLLOGDEVICESTDOUT_H_

#include "mglLogDevice.h"

class mglLogDeviceStdOut : public mglLogDevice
{
	void flush();

	void operator << (char* str);
	void operator << (const char* str);
	void operator << (string str);
	~mglLogDeviceStdOut();
};

#endif /* MGLLOGDEVICESTDOUT_H_ */
