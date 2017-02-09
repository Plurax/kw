/*
 * mglColor.cpp
 *
 *  Created on: 09.11.2013
 *      Author: chuhlich
 */

#include <stdlib.h>
#include <iostream>
#include "mglLogger.h"
#include "mglValColor.h"
#include "mglValString.h"
#include <cstring>

using namespace std;



mglValColor::mglValColor()
{
	fRed = 0.0;
	fGreen = 0.8;
	fBlue = 0.0;
	fAlpha = 0.0;
}

mglValColor::~mglValColor()
{
}

mglValColor::mglValColor(float red, float green, float blue, float alpha)
{
	fRed = red;
	fGreen = green;
	fBlue = blue;
	fAlpha = alpha;
}

mglValColor::mglValColor(const char* hex)
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
	
mglValString mglValColor::asString()
{
	std::stringstream str;
	str << "mglValColor: { " << fRed << ", " << fGreen << ", " << fBlue << ", " << fAlpha << "}";
	return mglValString(str.str());
}


std::ostream& operator<< (std::ostream& stream, const mglValColor& _valcolor)
{
	stream << "mglValColor: { R " << _valcolor.fRed << ", G " << _valcolor.fGreen << ", B " << _valcolor.fBlue << ", A " << _valcolor.fAlpha << " }";
	return stream;
}


mglValString mglValColor::getType()
{
	return mglValString("mglValColor");
}

