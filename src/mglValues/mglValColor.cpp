/*
 * mglColor.cpp
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#include <stdlib.h>
#include <iostream>
#include "mglDebug/mglLogger.h"
#include "mglValues/mglValColor.h"

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
	INIT_LOG("mglValColor", "mglColor(const char* hex)");

	const char* ptr = hex;
	// Assume we got RRGGBBAA:
	float* fPtr[4] = { &this->fRed, &this->fGreen, &this->fBlue, &this->fAlpha};

	if (hex[0] == '0' && hex[1] == 'x')
		ptr = &hex[2];

	int istop = 4;
	if (strlen(ptr) < 8)
	{
		istop = 3;
		fAlpha = 1.0;
	}

	for (int i = 0; i < istop; i++)
	{
		unsigned long x;
		char tmp[3];
		tmp[0] = ptr[i*2];
		tmp[1] = ptr[i*2+1];
		tmp[2] = '\0';

		x = strtoul(tmp, NULL, 16);
		if (x == 0)
			*fPtr[i] = 0.0f;
		else
			*fPtr[i] = 1.0f * ((float)x / 255.0);
	}
}

mglValString mglValColor::asString()
{
	std::stringstream str;
	str << "Color: { " << fRed << ", " << fGreen << ", " << fBlue << ", " << fAlpha << "}";
	return mglValString(str.str());
}


enumValType mglValColor::getType()
{
	return m_valType;
}
