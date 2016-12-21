/*
 * mglLogDeviceFile.cpp
 *
 *  Created on: 12.01.2014
 *      Author: cromas
 */





#include "mglDebug/mglLogDeviceFile.h"

void mglLogDeviceFile::flush()
{
	m_outputFile.flush();
}

mglLogDeviceFile::mglLogDeviceFile(const char* filename)
{
	m_outputFile.open (filename);
}


void mglLogDeviceFile::operator << (char* str)
{
	m_outputFile << str;
}

void mglLogDeviceFile::operator << (const char* str)
{
	m_outputFile << str;
}


void mglLogDeviceFile::operator << (string str)
{
	m_outputFile << str;
}


mglLogDeviceFile::~mglLogDeviceFile()
{
	m_outputFile.close();
}
