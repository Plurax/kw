/*
 * mglValFixedPoint.h
 *
 *  Created on: 13.11.2013
 *      Author: cromas
 */

#ifndef MGLVALFIXEDPOINT_H_
#define MGLVALFIXEDPOINT_H_

#include "mglValString.h"
#include "mglValue.h"

using namespace std;


enum class eValFixedPointPrec {
	prec15N2,
	prec13N4,
	prec11N6,
	prec9N8,
	prec7N10,
	prec5N12
};



class mglValFixedPoint : public mglValue
{
public:
  static const mglValType m_valType = mglValType::mglValFixedPoint;
	static const short precN[7];

	mglValFixedPoint();
	mglValFixedPoint(eValFixedPointPrec prec);
	mglValFixedPoint(long in, eValFixedPointPrec prec);
	mglValString asString();

	mglValType getType();

	bool operator >= (const mglValFixedPoint right);
	bool operator > (const mglValFixedPoint right);
	bool operator <= (const mglValFixedPoint right);
	bool operator < (const mglValFixedPoint right);
	mglValFixedPoint operator + (const mglValFixedPoint& right);
	mglValFixedPoint operator += (const mglValFixedPoint& right);
	mglValFixedPoint operator - (const mglValFixedPoint& right);
	mglValFixedPoint operator -= (const mglValFixedPoint& right);
	mglValFixedPoint operator * (const mglValFixedPoint& right);
	mglValFixedPoint operator / (const mglValFixedPoint& right);

	mglValFixedPoint getWithNewPrecision(eValFixedPointPrec prec);

private:
	long m_lValue;

	bool m_isEmpty;
	eValFixedPointPrec m_Precision;
};

//const short mglValFixedPoint::precN[7] = { 2, 4, 6, 8, 10, 12};

#endif /* MGLVALFIXEDPOINT_H_ */
