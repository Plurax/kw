/*
 * mglValFixedPoint.cpp
 *
 *  Created on: 13.11.2013
 *      Author: cromas
 */

#include "mglDebug/mglDebug.h"
#include "mglValues/mglValFixedPoint.h"

const short mglValFixedPoint::precN[7] = { 2, 4, 6, 8, 10, 12};


mglValFixedPoint::mglValFixedPoint()
{
	m_isEmpty = true;
	m_Precision = eValFixedPointPrec::prec11N6;
}

mglValFixedPoint::mglValFixedPoint(eValFixedPointPrec prec)
{
	m_isEmpty = true;
	m_Precision = prec;
}

mglValFixedPoint::mglValFixedPoint(long in, eValFixedPointPrec prec)
{
	m_lValue = in;
	m_Precision = prec;
	m_isEmpty = false;
}

mglValString mglValFixedPoint::asString()
{
	int i;
	char tmp[20] = "";
	snprintf(tmp, 20, "%ld", m_lValue);
	for (i = strlen(tmp); i > precN[ static_cast<int>(m_Precision)]; i--)
	{
		tmp[i+1]=tmp[i];
	}
	tmp[i] = '.';

	return mglValString(tmp);
}

bool mglValFixedPoint::operator >= (const mglValFixedPoint right)
{
	if (this->m_Precision == right.m_Precision)
	{
		return this->m_lValue >= right.m_lValue;
	}
	return false;
}

bool mglValFixedPoint::operator > (const mglValFixedPoint right)
{
	return m_lValue > right.m_lValue;
}

bool mglValFixedPoint::operator <= (const mglValFixedPoint right)
{
	return m_lValue <= right.m_lValue;
}

bool mglValFixedPoint::operator < (const mglValFixedPoint right)
{
	return m_lValue < right.m_lValue;
}

mglValFixedPoint mglValFixedPoint::operator + (const mglValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValFixedPoint", "operator +");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		INIT_LOG("mglValFixedPoint", "operator +");
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	return mglValFixedPoint(this->m_lValue + right.m_lValue, this->m_Precision);
}

mglValFixedPoint mglValFixedPoint::operator - (const mglValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValFixedPoint", "operator -");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		INIT_LOG("mglValFixedPoint", "operator -");
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	return mglValFixedPoint(this->m_lValue - right.m_lValue, this->m_Precision);
}

mglValFixedPoint mglValFixedPoint::operator * (const mglValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValFixedPoint", "operator *");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		INIT_LOG("mglValFixedPoint", "operator *");
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	return mglValFixedPoint(this->m_lValue * right.m_lValue, this->m_Precision);
}

mglValFixedPoint mglValFixedPoint::operator / (const mglValFixedPoint& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValFixedPoint", "operator /");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	if (this->m_Precision != right.m_Precision)
	{
		INIT_LOG("mglValFixedPoint", "operator /");
		THROW_TECHNICAL_EXCEPTION(3, "Operation not allowed - Precision differs between objects");
	}

	return mglValFixedPoint(this->m_lValue / right.m_lValue, this->m_Precision);

}

/**
 *	This will convert between different precision settings. There is no rounding made!
 */
mglValFixedPoint mglValFixedPoint::getWithNewPrecision(eValFixedPointPrec prec)
{
	if (this->m_isEmpty)
	{
		return mglValFixedPoint(prec);
	}

	switch ( static_cast<int>(prec) -  static_cast<int>(this->m_Precision))
	{
	case 2:
		return mglValFixedPoint(this->m_lValue * 100, prec);
		break;
	case 4:
		return mglValFixedPoint(this->m_lValue * 10000, prec);
		break;
	case 6:
		return mglValFixedPoint(this->m_lValue * 1000000, prec);
		break;
	case 8:
		return mglValFixedPoint(this->m_lValue * 100000000, prec);
		break;
	case 10:
		return mglValFixedPoint(this->m_lValue * 10000000000, prec);
		break;
	case 12:
		return mglValFixedPoint(this->m_lValue * 1000000000000, prec);
		break;

	case -2:
		return mglValFixedPoint(this->m_lValue / 100, prec);
		break;
	case -4:
		return mglValFixedPoint(this->m_lValue / 10000, prec);
		break;
	case -6:
		return mglValFixedPoint(this->m_lValue / 1000000, prec);
		break;
	case -8:
		return mglValFixedPoint(this->m_lValue / 100000000, prec);
		break;
	case -10:
		return mglValFixedPoint(this->m_lValue / 10000000000, prec);
		break;
	case -12:
		return mglValFixedPoint(this->m_lValue / 1000000000000, prec);
		break;
	default:
	{
		INIT_LOG("mglValFixedPoint", "getWithNewPrecision");
		THROW_TECHNICAL_EXCEPTION(22, "Error in precision conversion!");
	}
	}

}
