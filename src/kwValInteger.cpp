/*
 * kwValInteger.cpp
 *
 *  Created on: 26.10.2014
 *      Author: chuhlich
 */

#include <kw/kwValInteger.h>
#include "kwDebug.h"


kwValInteger::kwValInteger()
{
	m_Value = 0;
}

kwValInteger::kwValInteger(int val)
{
	m_Value = val;
}


kwValInteger::~kwValInteger()
{
}


int kwValInteger::getValue()
{
	return m_Value;
}

kwValString  kwValInteger::asString() const
{
    return kwValString(std::to_string(m_Value));
}

kwValInteger::operator int() const
{
    return m_Value;
}

std::ostream& operator<< (std::ostream& stream, const kwValInteger& _valinteger)
{
	stream << _valinteger.m_Value;
	return stream;
}

bool kwValInteger::operator == (const kwValInteger right)
{
	return this->m_Value == right.m_Value;
}

bool kwValInteger::operator != (const kwValInteger right)
{
	return !(this->m_Value == right.m_Value);
}

bool kwValInteger::operator >= (const kwValInteger right)
{
	return this->m_Value >= right.m_Value;
}

bool kwValInteger::operator > (const kwValInteger right)
{
	return m_Value > right.m_Value;
}

bool kwValInteger::operator <= (const kwValInteger right)
{
	return m_Value <= right.m_Value;
}

bool kwValInteger::operator < (const kwValInteger right)
{
	return m_Value < right.m_Value;
}

kwValInteger& kwValInteger::operator = (kwValInteger const& right)
{
	if (this != &right)
	{
		this->m_Value = right.m_Value;
	}
	return *this;
}

kwValInteger kwValInteger::operator + (const kwValInteger& right)
{
	return kwValInteger(this->m_Value + right.m_Value);
}

kwValInteger& kwValInteger::operator += (kwValInteger const& right)
{
	this->m_Value += right.m_Value;
	return *this;
}

kwValInteger kwValInteger::operator - (const kwValInteger& right)
{
	return kwValInteger(this->m_Value - right.m_Value);
}

kwValInteger& kwValInteger::operator -= (kwValInteger const& right)
{
	this->m_Value -= right.m_Value;
	return *this;
}

kwValInteger kwValInteger::operator * (const kwValInteger& right)
{
	return kwValInteger(this->m_Value * right.m_Value);
}


kwValInteger kwValInteger::operator / (const kwValInteger& right)
{
	return kwValInteger(this->m_Value / right.m_Value);
}


json kwValInteger::toJson()
{
    json j = m_Value;
    return j;
}
