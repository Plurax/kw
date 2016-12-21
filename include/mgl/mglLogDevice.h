/*
 * mglLogDevice.h
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */

#ifndef MGLLOGDEVICE_H_
#define MGLLOGDEVICE_H_

#include <iostream>
#include "mglValues/mglValString.h"

class mglLogDevice
{
public:
	virtual void flush() = 0;
	virtual void operator << (char* str) = 0;
	virtual void operator << (const char* str) = 0;
	virtual void operator << (string str) = 0;

};

#endif /* MGLLOGDEVICE_H_ */