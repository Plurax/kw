/*
 * mglLogDeviceStdErr.h
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */

#ifndef MGLLOGDEVICESTDERR_H_
#define MGLLOGDEVICESTDERR_H_



#include "mglLogDevice.h"


class mglLogDeviceStdErr : public mglLogDevice
{
	void flush();

	void operator << (char* str);
	void operator << (std::string str);
	~mglLogDeviceStdErr();
};

#endif /* MGLLOGDEVICESTDERR_H_ */
