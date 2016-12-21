/*
 * mglValInteger.cpp
 *
 *  Created on: 26.10.2014
 *      Author: cromas
 */

#include <mglValues/mglValInteger.h>
#include "mglDebug/mglDebug.h"


mglValInteger::mglValInteger()
{
	// TODO Auto-generated constructor stub
	m_Value = 0;
	m_isEmpty = true;
}

mglValInteger::mglValInteger(int val)
{
	// TODO Auto-generated constructor stub
	m_Value = val;
	m_isEmpty = false;
}


mglValInteger::~mglValInteger()
{

}


int mglValInteger::getValue()
{
	return m_Value;
}

std::ostream& operator<< (std::ostream& stream, const mglValInteger& _valinteger)
{
	stream << _valinteger.m_Value;
	return stream;
}


bool mglValInteger::operator >= (const mglValInteger right)
{
	return this->m_Value >= right.m_Value;
}

bool mglValInteger::operator > (const mglValInteger right)
{
	return m_Value > right.m_Value;
}

bool mglValInteger::operator <= (const mglValInteger right)
{
	return m_Value <= right.m_Value;
}

bool mglValInteger::operator < (const mglValInteger right)
{
	return m_Value < right.m_Value;
}

mglValInteger& mglValInteger::operator = (mglValInteger const& right)
{
	if (this != &right)
	{
		this->m_isEmpty = right.m_isEmpty;
		this->m_Value = right.m_Value;
	}
	return *this;
}

mglValInteger mglValInteger::operator + (const mglValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValInteger", "operator +");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}
	return mglValInteger(this->m_Value + right.m_Value);
}

mglValInteger& mglValInteger::operator += (mglValInteger const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValInteger", "operator +=");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	this->m_Value += right.m_Value;
	return *this;
}

mglValInteger mglValInteger::operator - (const mglValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValInteger", "operator -");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return mglValInteger(this->m_Value - right.m_Value);
}

mglValInteger& mglValInteger::operator -= (mglValInteger const& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValInteger", "operator -");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	this->m_Value -= right.m_Value;
	return *this;
}

mglValInteger mglValInteger::operator * (const mglValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValInteger", "operator *");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return mglValInteger(this->m_Value * right.m_Value);
}


mglValInteger mglValInteger::operator / (const mglValInteger& right)
{
	if (this->m_isEmpty || right.m_isEmpty)
	{
		INIT_LOG("mglValInteger", "operator /");
		THROW_TECHNICAL_EXCEPTION(2, "Operation not allowed - object NULL");
	}

	return mglValInteger(this->m_Value / right.m_Value);
}
