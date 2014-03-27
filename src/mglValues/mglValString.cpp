/*
 * mglValString.cpp
 *
 *  Created on: 28.02.2014
 *      Author: cromas
 */



#include "mglValues/mglValString.h"

mglValString::mglValString()
{
	m_string = NULL;
	m_isEmpty = true;
}


mglValString::mglValString(char* _cstr)
{
	m_string = new string(_cstr);
	m_isEmpty = false;
}


mglValString::mglValString(const char* _cstr)
{
	m_string = new string(_cstr);
	m_isEmpty = false;
}


mglValString::mglValString(string& _str)
{
	m_string = new string(_str);
	m_isEmpty = false;
}


mglValString::mglValString(string* _str)
{
	m_string = new string(*_str);
	m_isEmpty = false;
}


mglValString::mglValString(const string _str)
{
	m_string = new string(_str);
	m_isEmpty = false;
}


mglValString::mglValString(mglValString*_str)
{
	m_string = new string(*_str->str());
	m_isEmpty = false;
}


mglValString::mglValString(const mglValString& right) // Copy constructor
{
	m_string = new string(*right.m_string);
	m_isEmpty = false;
}


mglValString::~mglValString()
{
	delete m_string;
}

int mglValString::size()
{
	return m_string->size();
}


bool mglValString::empty()
{
	return m_isEmpty;
}


mglValString& mglValString::erase (size_t pos, size_t len)
{
	m_string->erase(pos, len);
}


mglValString mglValString::operator + (const mglValString& _right)
{
	return mglValString(*this->m_string + *_right.m_string);
}

bool mglValString::operator == (const mglValString& _right)
{
	return this->m_string == _right.m_string;
}


mglValString& mglValString::operator = (const mglValString& _str)
{
	// First check if the local helds already a string - this must be deleted to avoid mem leak caused by overwriting the value!
	if (this->m_string != NULL)
	{
		delete this->m_string;
		this->m_string = NULL;
	}

	if (_str.m_string != NULL)
	{
		this->m_string = new string(*_str.m_string);
	}

	return *this;
}


bool mglValString::operator < (const mglValString& _right) const
{
	return ((*this->m_string) < (*_right.m_string));
}


const string* mglValString::str() const
{
	return m_string;
}

enumValType mglValString::getType()
{
	return m_valType;
}
