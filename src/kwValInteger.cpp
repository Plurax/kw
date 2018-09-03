/*
 * kwValInteger.cpp
 *
 *  Created on: 26.10.2014
 *      Author: chuhlich
 */

#include <kwValInteger.h>
#include "kwDebug.h"


kwValInteger::kwValInteger()
{
	// TODO Auto-generated constructor stub
	m_Value = 0;
	m_isEmpty = true;
}

kwValInteger::kwValInteger(int val)
{
	// TODO Auto-generated constructor stub
	m_Value = val;
	m_isEmpty = false;
}


kwValInteger::~kwValInteger()
{

}


int kwValInteger::getValue()
{
	return m_Value;
}

std::string  kwValInteger::asString()
{
  return std::to_string(m_Value);
}

std::ostream& operator<< (std::ostream& stream, const kwValInteger& _valinteger)
{
	stream << _valinteger.m_Value;
	return stream;
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
		this->m_isEmpty = right.m_isEmpty;
		this->m_Value = right.m_Value;
	}
	return *this;
}

kwValInteger kwValInteger::operator + (const kwValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	return kwValInteger(this->m_Value + right.m_Value);
}

kwValInteger& kwValInteger::operator += (kwValInteger const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	this->m_Value += right.m_Value;
	return *this;
}

kwValInteger kwValInteger::operator - (const kwValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return kwValInteger(this->m_Value - right.m_Value);
}

kwValInteger& kwValInteger::operator -= (kwValInteger const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	this->m_Value -= right.m_Value;
	return *this;
}

kwValInteger kwValInteger::operator * (const kwValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return kwValInteger(this->m_Value * right.m_Value);
}


kwValInteger kwValInteger::operator / (const kwValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return kwValInteger(this->m_Value / right.m_Value);
}
