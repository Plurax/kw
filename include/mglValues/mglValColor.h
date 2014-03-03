/*
 * mglColor.h
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#ifndef MGLCOLOR_H_
#define MGLCOLOR_H_


#include "mglValString.h"
#include "mglValue.h"

class mglValColor : public mglValue
{
public:
  static const mglValType m_valType = mglValType::mglValColor;
	mglValColor();
	mglValColor(float red, float green, float blue, float alpha);
	mglValColor(const char* hex);

	mglValString asString();
	mglValType getType();

	float fRed;
	float fGreen;
	float fBlue;
	float fAlpha;
};

#endif /* MGLCOLOR_H_ */
