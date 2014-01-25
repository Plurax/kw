/*
 * mglColor.h
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#ifndef MGLCOLOR_H_
#define MGLCOLOR_H_


#include <string>

class mglValColor {
public:
	mglValColor();
	mglValColor(float red, float green, float blue, float alpha);
	mglValColor(const char* hex);

	std::string asString();

	float fRed;
	float fGreen;
	float fBlue;
	float fAlpha;
};

#endif /* MGLCOLOR_H_ */