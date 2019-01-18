/*
 * kwValUnsignedInteger.cpp
 *
 *  Created on: 8.10.2018
 *      Author: chuhlich
 */

#include <kw/kwValUnsignedInteger.h>
#include "kwDebug.h"


kwValUnsignedInteger::kwValUnsignedInteger()
{
	// TODO Auto-generated constructor stub
	m_Value = 0;
	m_isEmpty = true;
}

kwValUnsignedInteger::kwValUnsignedInteger(uint val)
{
	// TODO Auto-generated constructor stub
	m_Value = val;
	m_isEmpty = false;
}


kwValUnsignedInteger::~kwValUnsignedInteger()
{

}


uint kwValUnsignedInteger::getValue()
{
	return m_Value;
}

kwValString  kwValUnsignedInteger::asString()
{
    return kwValString(std::to_string(m_Value));
}

kwValUnsignedInteger::operator uint() const
{
    if (m_isEmpty)
        return 0;
    else
        return m_Value;
}

std::ostream& operator<< (std::ostream& stream, const kwValUnsignedInteger& _valinteger)
{
	stream << _valinteger.m_Value;
	return stream;
}


bool kwValUnsignedInteger::operator >= (const kwValUnsignedInteger right)
{
	return this->m_Value >= right.m_Value;
}

bool kwValUnsignedInteger::operator > (const kwValUnsignedInteger right)
{
	return m_Value > right.m_Value;
}

bool kwValUnsignedInteger::operator <= (const kwValUnsignedInteger right)
{
	return m_Value <= right.m_Value;
}

bool kwValUnsignedInteger::operator < (const kwValUnsignedInteger right)
{
	return m_Value < right.m_Value;
}

kwValUnsignedInteger& kwValUnsignedInteger::operator = (kwValUnsignedInteger const& right)
{
	if (this != &right)
	{
		this->m_isEmpty = right.m_isEmpty;
		this->m_Value = right.m_Value;
	}
	return *this;
}

kwValUnsignedInteger kwValUnsignedInteger::operator + (const kwValUnsignedInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	return kwValUnsignedInteger(this->m_Value + right.m_Value);
}

kwValUnsignedInteger& kwValUnsignedInteger::operator += (kwValUnsignedInteger const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	this->m_Value += right.m_Value;
	return *this;
}

kwValUnsignedInteger kwValUnsignedInteger::operator - (const kwValUnsignedInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return kwValUnsignedInteger(this->m_Value - right.m_Value);
}

kwValUnsignedInteger& kwValUnsignedInteger::operator -= (kwValUnsignedInteger const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	this->m_Value -= right.m_Value;
	return *this;
}

kwValUnsignedInteger kwValUnsignedInteger::operator * (const kwValUnsignedInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return kwValUnsignedInteger(this->m_Value * right.m_Value);
}


kwValUnsignedInteger kwValUnsignedInteger::operator / (const kwValUnsignedInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return kwValUnsignedInteger(this->m_Value / right.m_Value);
}


json kwValUnsignedInteger::toJson()
{
    json j = m_Value;
    return j;
}
