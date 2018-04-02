/*
 * kwValString.cpp
 *
 *  Created on: 28.02.2014
 *      Author: chuhlich
 */



#include "kwValString.h"



kwValString::kwValString()
{
	m_string = make_shared<string>("");
	m_isEmpty = true;
}


kwValString::kwValString(char* _cstr)
{
	m_string = make_shared<string>(_cstr);
	m_isEmpty = false;
}


kwValString::kwValString(const char* _cstr)
{
	m_string = make_shared<string>(_cstr);
	m_isEmpty = false;
}


kwValString::kwValString(string& _str)
{
	m_string = make_shared<string>(_str);
	m_isEmpty = false;
}


kwValString::kwValString(string* _str)
{
	m_string = make_shared<string>(*_str);
	m_isEmpty = false;
}


kwValString::kwValString(const string _str)
{
	m_string = make_shared<string>(_str);
	m_isEmpty = false;
}


kwValString::kwValString(kwValString*_str)
{
	m_string = make_shared<string>(*_str->str());
	m_isEmpty = false;
}

kwValString::kwValString(shared_ptr<kwValString> _str)
{
	m_string = make_shared<string>(*_str->str());
	m_isEmpty = false;
}

kwValString::kwValString(const kwValString& right) // Copy constructor
{
	m_string = make_shared<string>(*right.m_string);
	m_isEmpty = false;
}


kwValString::~kwValString()
{
// nothing to do as string is kept as smart pointer
}


std::ostream& operator<< (std::ostream& stream, const kwValString& _valstring)
{
		  stream << (*_valstring.const_str());
		  return stream;
}


int kwValString::size()
{
	if (m_string != NULL)
		return m_string->size();
	else
	{
		return 0;
	}
}


bool kwValString::empty() const
{
	return m_isEmpty;
}


void kwValString::erase (int pos, int len)
{
	if (m_string != NULL)
		m_string->erase(pos, len);
}


kwValString kwValString::operator + (const kwValString& _right)
{
	if (!this->empty())
		return kwValString(*this->m_string + *_right.m_string);
	else
	{
	// IS adding a string to an undefined string the string or is in an error?
		if (!_right.empty())
			return kwValString(_right);
		else
			return kwValString();
	}
}

bool kwValString::operator == (const kwValString& _right)
{
	if (m_string != NULL)
		return (this->m_string->compare(*_right.m_string) == 0);
	else
		return false;
}


kwValString& kwValString::operator = (const kwValString& _str)
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


bool kwValString::operator < (const kwValString& _right) const
{
	return ((*this->m_string) < (*_right.m_string));
}


shared_ptr<string> kwValString::str()
{
	return m_string;
}

const shared_ptr<string> kwValString::const_str() const
{
	const shared_ptr<string> clone = make_shared<string>(m_string->c_str());
	return clone;
}

kwValString kwValString::getType()
{
	return kwValString("kwValString");
}

const char* kwValString::c_str()
{
  return m_string->c_str();
}
