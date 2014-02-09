/*
 * mglValFixedPoint.h
 *
 *  Created on: 13.11.2013
 *      Author: cromas
 */

#ifndef MGLVALFIXEDPOINT_H_
#define MGLVALFIXEDPOINT_H_

#include <string>

using namespace std;


enum class eValFixedPointPrec = {
		prec10n4,
		prec10n6,
		prec10n8,
		prec12n4,
		prec12n6,
		prec14n2,
		prec14n4
};



class mglValFixedPoint
{
public:
	mglValFixedPoint();
	mglValFixedPoint(long in, eValFixedPointPrec prec);
	string asString();

	bool operator >= (const mglValFixedPoint& right);
	bool operator > (const mglValFixedPoint& right);
	bool operator <= (const mglValFixedPoint& right);
	bool operator < (const mglValFixedPoint& right);
	mglValFixedPoint& operator + (const mglValFixedPoint& right);
	mglValFixedPoint& operator - (const mglValFixedPoint& right);
	mglValFixedPoint& operator * (const mglValFixedPoint& right);
	mglValFixedPoint& operator / (const mglValFixedPoint& right);

	mglValFixedPoint& getWithNewPrecision(eValFixedPointPrec prec);

private:
	long m_lValue;

	bool m_isEmpty;
	eValFixedPointPrec m_Precision;
};

#endif /* MGLVALFIXEDPOINT_H_ */
