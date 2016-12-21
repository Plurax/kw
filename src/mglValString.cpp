/*
 * mglValString.cpp
 *
 *  Created on: 28.02.2014
 *      Author: cromas
 */



#include "mglValString.h"



mglValString::mglValString()
{
	m_string = make_shared<string>("");
	m_isEmpty = true;
}


mglValString::mglValString(char* _cstr)
{
	m_string = make_shared<string>(_cstr);
	m_isEmpty = false;
}


mglValString::mglValString(const char* _cstr)
{
	m_string = make_shared<string>(_cstr);
	m_isEmpty = false;
}


mglValString::mglValString(string& _str)
{
	m_string = make_shared<string>(_str);
	m_isEmpty = false;
}


mglValString::mglValString(string* _str)
{
	m_string = make_shared<string>(*_str);
	m_isEmpty = false;
}


mglValString::mglValString(const string _str)
{
	m_string = make_shared<string>(_str);
	m_isEmpty = false;
}


mglValString::mglValString(mglValString*_str)
{
	m_string = make_shared<string>(*_str->str());
	m_isEmpty = false;
}

mglValString::mglValString(shared_ptr<mglValString> _str)
{
	m_string = make_shared<string>(*_str->str());
	m_isEmpty = false;
}

mglValString::mglValString(const mglValString& right) // Copy constructor
{
	m_string = make_shared<string>(*right.m_string);
	m_isEmpty = false;
}


mglValString::~mglValString()
{
// nothing to do as string is kept as smart pointer
}


std::ostream& operator<< (std::ostream& stream, const mglValString& _valstring)
{
		  stream << (*_valstring.const_str());
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


bool mglValString::empty() const
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
	if (!this->empty())
		return mglValString(*this->m_string + *_right.m_string);
	else
	{
	// IS adding a string to an undefined string the string or is in an error?
		if (!_right.empty())
			return mglValString(_right);
		else
			return mglValString();
	}
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
		this->m_string = NULL;
	}

	if (_str.m_string != NULL)
	{
		this->m_string = make_shared<string>(*_str.m_string);
	}

	return *this;
}


bool mglValString::operator < (const mglValString& _right) const
{
	return ((*this->m_string) < (*_right.m_string));
}


shared_ptr<string> mglValString::str()
{
	return m_string;
}

const shared_ptr<string> mglValString::const_str() const
{
	const shared_ptr<string> clone = make_shared<string>(m_string->c_str());
	return clone;
}

mglValString mglValString::getType()
{
	return mglValString("mglValString");
}
