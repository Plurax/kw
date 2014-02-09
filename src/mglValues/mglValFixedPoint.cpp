/*
 * mglValFixedPoint.cpp
 *
 *  Created on: 13.11.2013
 *      Author: cromas
 */

#include "mglValues/mglValFixedPoint.h"


mglValFixedPoint::mglValFixedPoint()
{
	m_isEmpty = true;
}

mglValFixedPoint::mglValFixedPoint(long in, eValFixedPointPrec prec)
{
	m_lValue = in;
	m_Precision = prec;
	m_isEmpty = false;
}

string mglValFixedPoint::asString()
{

}

mglValFixedPoint& mglValFixedPoint::operator >= (const mglValFixedPoint& right)
{
	if (this->m_Precision == right.m_Precision)
	{
		return this->m_lValue >= right.m_lValue;
	}
}

mglValFixedPoint& mglValFixedPoint::operator > (const mglValFixedPoint& right)
{

}

mglValFixedPoint& mglValFixedPoint::operator <= (const mglValFixedPoint& right)
{

}

mglValFixedPoint& mglValFixedPoint::operator < (const mglValFixedPoint& right)
{

}

mglValFixedPoint& mglValFixedPoint::operator + (const mglValFixedPoint& right)
{

}

mglValFixedPoint& mglValFixedPoint::operator - (const mglValFixedPoint& right)
{

}

mglValFixedPoint& mglValFixedPoint::operator * (const mglValFixedPoint& right)
{

}

mglValFixedPoint& mglValFixedPoint::operator / (const mglValFixedPoint& right)
{

}

mglValFixedPoint& mglValFixedPoint::getWithNewPrecision(eValFixedPointPrec prec)
{

}
