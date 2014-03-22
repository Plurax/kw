/*
 * mglValue.h
 *
 *  Created on: 19.02.2014
 *      Author: cromas
 */

#ifndef MGLVALUE_H_
#define MGLVALUE_H_

class mglValString;

enum class enumValType { mglValUndefined, mglValFixedPoint, mglValString, mglValInteger, mglValFloat, mglValColor, mglValCoord};

class mglValue
{
public:
	mglValue();
	virtual enumValType getType();
	//virtual mglValString serialize();
};

#endif /* MGLVALUE_H_ */
