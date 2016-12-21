/*
 * mglLogDeviceStdErr.cpp
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */





#include "mglLogDeviceStdErr.h"

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

void mglLogDeviceStdErr::operator << (string str)
{
	std::cerr << str;
}


mglLogDeviceStdErr::~mglLogDeviceStdErr()
{

}
