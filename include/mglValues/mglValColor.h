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
	mglValColor();
	~mglValColor();
	mglValColor(float red, float green, float blue, float alpha);
	mglValColor(const char* hex);

	friend std::ostream& operator<< (std::ostream& stream, const mglValColor& _valcolor);

	mglValString asString();
	mglValString getType();

	float fRed;
	float fGreen;
	float fBlue;
	float fAlpha;

private:
	static const mglValString m_valType;
};

#endif /* MGLCOLOR_H_ */
