/*
 * mglLogDeviceStdOut.cpp
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */



#include "mglLogger/mglLogDeviceStdOut.h"

void mglLogDeviceStdOut::flush()
{

}



void mglLogDeviceStdOut::operator << (char* str)
{
	std::cout << str;
}


void mglLogDeviceStdOut::operator << (std::string str)
{
	std::cout << str;
}

mglLogDeviceStdOut::~mglLogDeviceStdOut()
{

}
