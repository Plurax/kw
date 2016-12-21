/*
 * mglLogDeviceStdOut.cpp
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */



#include "mglDebug/mglLogDeviceStdOut.h"

void mglLogDeviceStdOut::flush()
{

}



void mglLogDeviceStdOut::operator << (char* str)
{
	std::cout << str;
}

void mglLogDeviceStdOut::operator << (const char* str)
{
	std::cout << str;
}


void mglLogDeviceStdOut::operator << (string str)
{
	std::cout << str;
}

mglLogDeviceStdOut::~mglLogDeviceStdOut()
{

}
