/*
 * kwColor.h
 *
 *  Created on: 09.11.2013
 *      Author: chuhlich
 */

#ifndef KWCOLOR_H_
#define KWCOLOR_H_


#include "kwValString.h"
#include "kwValue.h"

class kwValColor : public kwValue
{
public:
	kwValColor();
	~kwValColor();
	kwValColor(float red, float green, float blue, float alpha);
	kwValColor(const char* hex);

	friend std::ostream& operator<< (std::ostream& stream, const kwValColor& _valcolor);

	kwValString asString();
	kwValString getType();

	float fRed;
	float fGreen;
	float fBlue;
	float fAlpha;

private:
	static const kwValString m_valType;
};

#endif /* KWCOLOR_H_ */
