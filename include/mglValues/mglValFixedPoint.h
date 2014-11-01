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

static const char* enumValFixedPointPrecNames[] = { "prec15N2", "prec13N4", "prec11N6", "prec9N8", "prec7N10", "prec5N12" };
enum class enumValFixedPointPrec {
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
	static const short precN[7];
	static const long precNScalings[7];

	mglValFixedPoint();
	~mglValFixedPoint();
	mglValFixedPoint(mglValString _string);
	mglValFixedPoint(enumValFixedPointPrec prec);
	mglValFixedPoint(long in, enumValFixedPointPrec prec);
	mglValString asString() const;

	mglValString getType();

	friend std::ostream& operator<< (std::ostream& stream, const mglValFixedPoint& _valfixedpoint);

	bool operator >= (const mglValFixedPoint right);
	bool operator > (const mglValFixedPoint right);
	bool operator <= (const mglValFixedPoint right);
	bool operator < (const mglValFixedPoint right);
	mglValFixedPoint& operator = (mglValFixedPoint const& right);
	mglValFixedPoint operator + (const mglValFixedPoint& right);
	mglValFixedPoint& operator += (mglValFixedPoint const& right);
	mglValFixedPoint operator - (const mglValFixedPoint& right);
	mglValFixedPoint& operator -= (mglValFixedPoint const& right);
	mglValFixedPoint operator * (const mglValFixedPoint& right);
	mglValFixedPoint operator / (const mglValFixedPoint& right);

	mglValFixedPoint getWithNewPrecision(enumValFixedPointPrec prec);

	enumValFixedPointPrec getPrecision();

	float asFloat();
private:
	static enumValFixedPointPrec getPrecisionFromString(char* _str);
	long m_lValue;

	bool m_isEmpty;
	enumValFixedPointPrec m_Precision;
};

//const short mglValFixedPoint::precN[7] = { 2, 4, 6, 8, 10, 12};

#endif /* MGLVALFIXEDPOINT_H_ */
