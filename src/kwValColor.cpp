/*
 * kwColor.cpp
 *
 *  Created on: 09.11.2013
 *      Author: chuhlich
 */

#include <stdlib.h>
#include <iostream>
#include "kwLogger.h"
#include "kwValColor.h"
#include "kwValString.h"
#include <cstring>

using namespace std;



kwValColor::kwValColor()
{
	fRed = 0.0;
	fGreen = 0.8;
	fBlue = 0.0;
	fAlpha = 0.0;
}

kwValColor::~kwValColor()
{
}

kwValColor::kwValColor(float red, float green, float blue, float alpha)
{
	fRed = red;
	fGreen = green;
	fBlue = blue;
	fAlpha = alpha;
}

kwValColor::kwValColor(const char* hex)
{
	const char* ptr = hex;
	// Assume we got RRGGBBAA:

	if (hex[0] == '0' && hex[1] == 'x')
		ptr = &hex[2];

	int istop = 3;
	if (strlen(ptr) < 8)
	{
		istop = 2;
	}

	unsigned long x;
	x = strtoul(hex, NULL, 16);

	if (istop == 3)
	{
		fRed = 1.0f * ((float)(0xFF & (x >> 32)) / 255.0);
		fGreen = 1.0f * ((float)(0xFF & (x >> 16)) / 255.0);
		fBlue = 1.0f * ((float)(0xFF & (x >> 8)) / 255.0);
		fAlpha = 1.0f * ((float)(0xFF & x) / 255.0);
	}
	else
	{
		fRed = 1.0f * ((float)(0xFF & (x >> 16)) / 255.0);
		fGreen = 1.0f * ((float)(0xFF & (x >> 8)) / 255.0);
		fBlue = 1.0f * ((float)(0xFF & x) / 255.0);
		fAlpha = 1.0f;
	}
}
	
std::string kwValColor::asString()
{
	std::stringstream str;
	str << "kwValColor: { " << fRed << ", " << fGreen << ", " << fBlue << ", " << fAlpha << "}";
	return str.str();
}


std::ostream& operator<< (std::ostream& stream, const kwValColor& _valcolor)
{
	stream << "kwValColor: { R " << _valcolor.fRed << ", G " << _valcolor.fGreen << ", B " << _valcolor.fBlue << ", A " << _valcolor.fAlpha << " }";
	return stream;
}


kwValString kwValColor::getType()
{
	return kwValString("kwValColor");
}

