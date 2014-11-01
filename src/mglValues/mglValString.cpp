/*
 * mglValString.cpp
 *
 *  Created on: 28.02.2014
 *      Author: cromas
 */



#include "mglValues/mglValString.h"



mglValString::mglValString()
{
	m_string = new string("");
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
	if (m_string != NULL)
		delete m_string;
}


std::ostream& operator<< (std::ostream& stream, const mglValString& _valstring)
{
		  stream << (*_valstring.str());
		  return stream;
}


int mglValString::size()
{
	if (m_string != NULL)
		return m_string->size();
	else
	{
		return 0;
	}
}


bool mglValString::empty()
{
	return m_isEmpty;
}


void mglValString::erase (int pos, int len)
{
	if (m_string != NULL)
		m_string->erase(pos, len);
}


mglValString mglValString::operator + (const mglValString& _right)
{
	if (this->m_string != NULL)
		return mglValString(*this->m_string + *_right.m_string);
}

bool mglValString::operator == (const mglValString& _right)
{
	if (m_string != NULL)
		return (this->m_string->compare(*_right.m_string) == 0);
	else
		return false;
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

mglValString mglValString::getType()
{
	return mglValString("mglValString");
}
