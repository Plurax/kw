/*
 * kwValFixedPoint.h
 *
 *  Created on: 13.11.2013
 *      Author: chuhlich
 */

#ifndef KWVALFIXEDPOINT_H_
#define KWVALFIXEDPOINT_H_

#include "kw/api.h"
#include "kw/kwValString.h"
#include "kw/kwValue.h"

using namespace std;

static const char* enumValFixedPointPrecNames[] = { "prec15N2", "prec13N4", "prec11N6", "prec9N8", "prec7N10", "prec5N12" };
enum class enumValFixedPointPrec {
	prec15N2 = 0,
	prec13N4,
	prec11N6,
	prec9N8,
	prec7N10,
	prec5N12
};



class DLL_PUBLIC kwValFixedPoint : public kwValue<kwValString>
{
public:
	static const short precN[7];
	static const long long precNScalings[7];

	kwValFixedPoint();
	~kwValFixedPoint();
	kwValFixedPoint(kwValString _string);
	kwValFixedPoint(enumValFixedPointPrec prec);
	kwValFixedPoint(long in, enumValFixedPointPrec prec);
  std::string asString() const;

	kwValString getType();

	friend std::ostream& operator<< (std::ostream& stream, const kwValFixedPoint& _valfixedpoint);
    json toJson() override;

	bool operator >= (const kwValFixedPoint right);
	bool operator > (const kwValFixedPoint right);
	bool operator <= (const kwValFixedPoint right);
	bool operator < (const kwValFixedPoint right);
	kwValFixedPoint& operator = (kwValFixedPoint const& right);
	kwValFixedPoint operator + (const kwValFixedPoint& right);
	kwValFixedPoint& operator += (kwValFixedPoint const& right);
	kwValFixedPoint operator - (const kwValFixedPoint& right);
	kwValFixedPoint& operator -= (kwValFixedPoint const& right);
	kwValFixedPoint operator * (const kwValFixedPoint& right);
	kwValFixedPoint operator / (const kwValFixedPoint& right);

	kwValFixedPoint getWithNewPrecision(enumValFixedPointPrec prec);

	enumValFixedPointPrec getPrecision();

	float asFloat();
    kwValString asString();
private:
	static enumValFixedPointPrec getPrecisionFromString(char* _str);
	long m_lValue;

	bool m_isEmpty;
	enumValFixedPointPrec m_Precision;
};

//const short kwValFixedPoint::precN[7] = { 2, 4, 6, 8, 10, 12};

#endif /* KWVALFIXEDPOINT_H_ */
