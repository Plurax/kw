/*
 * mglLogDeviceStdErr.cpp
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */





#include "mglDebug/mglLogDeviceStdErr.h"

void mglLogDeviceStdErr::flush()
{

}

void mglLogDeviceStdErr::operator << (char* str)
{
	std::cerr << str;
}

void mglLogDeviceStdErr::operator << (const char* str)
{
	std::cerr << str;
}

void mglLogDeviceStdErr::operator << (std::string str)
{
	std::cerr << str;
}


mglLogDeviceStdErr::~mglLogDeviceStdErr()
{

}
