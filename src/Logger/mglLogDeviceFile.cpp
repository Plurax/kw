/*
 * mglLogDeviceFile.cpp
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */





#include "mglLogDeviceFile.h"

void mglLogDeviceFile::flush()
{

}

mglLogDeviceFile::mglLogDeviceFile(const char* filename)
{

}


void mglLogDeviceFile::operator << (char* str)
{
	std::cout << str;
}


void mglLogDeviceFile::operator << (std::string str)
{
	std::cout << str;
}


mglLogDeviceFile::~mglLogDeviceFile()
{

}
