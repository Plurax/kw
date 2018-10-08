/*
 * kwValFloat.cpp
 *
 *  Created on: 8.10.2018
 *      Author: chuhlich
 */

#include <kw/kwValFloat.h>
#include "kwDebug.h"


kwValFloat::kwValFloat()
{
	m_Value = 0;
}

kwValFloat::kwValFloat(float val)
{
	m_Value = val;
}


kwValFloat::~kwValFloat()
{
}


float kwValFloat::getValue()
{
	return m_Value;
}

kwValString  kwValFloat::asString()
{
    return kwValString(std::to_string(m_Value));
}

kwValFloat::operator float() const
{
    return m_Value;
}

std::ostream& operator<< (std::ostream& stream, const kwValFloat& _valfloat)
{
	stream << _valfloat.m_Value;
	return stream;
}


bool kwValFloat::operator >= (const kwValFloat right)
{
	return this->m_Value >= right.m_Value;
}

bool kwValFloat::operator > (const kwValFloat right)
{
	return m_Value > right.m_Value;
}

bool kwValFloat::operator <= (const kwValFloat right)
{
	return m_Value <= right.m_Value;
}

bool kwValFloat::operator < (const kwValFloat right)
{
	return m_Value < right.m_Value;
}

kwValFloat& kwValFloat::operator = (kwValFloat const& right)
{
	if (this != &right)
	{
		this->m_Value = right.m_Value;
	}
	return *this;
}

kwValFloat kwValFloat::operator + (const kwValFloat& right)
{
	return kwValFloat(this->m_Value + right.m_Value);
}

kwValFloat& kwValFloat::operator += (kwValFloat const& right)
{
	this->m_Value += right.m_Value;
	return *this;
}

kwValFloat kwValFloat::operator - (const kwValFloat& right)
{
	return kwValFloat(this->m_Value - right.m_Value);
}

kwValFloat& kwValFloat::operator -= (kwValFloat const& right)
{
	this->m_Value -= right.m_Value;
	return *this;
}

kwValFloat kwValFloat::operator * (const kwValFloat& right)
{
	return kwValFloat(this->m_Value * right.m_Value);
}


kwValFloat kwValFloat::operator / (const kwValFloat& right)
{
	return kwValFloat(this->m_Value / right.m_Value);
}


json kwValFloat::toJson()
{
    json j = m_Value;
    return j;
}
