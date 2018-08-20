/*
 * kwValString.cpp
 *
 *  Created on: 28.02.2014
 *      Author: chuhlich
 */

#include "kwValString.h"



kwValString::kwValString()
{
  m_string = string("");
  m_isEmpty = true;
}


kwValString::kwValString(char* _cstr)
{
  m_string = string(_cstr);
  m_isEmpty = false;
}


kwValString::kwValString(const char* _cstr)
{
  m_string = string(_cstr);
  m_isEmpty = false;
}


kwValString::kwValString(string& _str)
{
  m_string = string(_str);
  m_isEmpty = false;
}

const char* kwValString::data()
{
  return m_string.data();
}

void kwValString::clear()
{
  m_string.clear();
}

void kwValString::push_back(char c)
{
  m_string.push_back(c);
}

kwValString::kwValString(string* _str)
{
  m_string = string(*_str);
  m_isEmpty = false;
}


kwValString::kwValString(const string _str)
{
  m_string = string(_str);
  m_isEmpty = false;
}


kwValString::kwValString(kwValString*_str)
{
  m_string = string(_str->str());
  m_isEmpty = false;
}

kwValString::kwValString(shared_ptr<kwValString> _str)
{
  m_string = string(_str->str());
  m_isEmpty = false;
}

kwValString::kwValString(const kwValString& right) // Copy constructor
{
  m_string = string(right.m_string);
  m_isEmpty = false;
}


kwValString::~kwValString()
{
}


std::ostream& operator<< (std::ostream& stream, const kwValString& _valstring)
{
  stream << (_valstring.const_str());
  return stream;
}


int kwValString::size()
{
  return m_string.size();
}


bool kwValString::empty() const
{
  return m_isEmpty;
}


void kwValString::erase (int pos, int len)
{
  m_string.erase(pos, len);
}


kwValString kwValString::operator + (const kwValString& _right)
{
  if (!this->empty())
    return kwValString(this->m_string + _right.m_string);
  else
  {
	// IS adding a string to an undefined string the string or is in an error?
    if (!_right.empty())
      return kwValString(_right);
    else
      return kwValString();
  }
}

bool kwValString::operator == (const kwValString& rhs) const
{
  return (m_string == rhs.m_string);
}


kwValString& kwValString::operator = (const kwValString& _str)
{
  this->m_string = string(_str.m_string);

  return *this;
}

kwValString& kwValString::operator = (const string& _str)
{
  // First check if the local helds already a string - this must be deleted to avoid mem leak caused by overwriting the value!
  this->m_string = _str;

  return *this;
}


bool kwValString::operator < (const kwValString& _right) const
{
  return ((this->m_string) < (_right.m_string));
}

bool kwValString::operator > (const kwValString& _right) const
{
  return ((this->m_string) > (_right.m_string));
}

string kwValString::str()
{
  return m_string;
}

const string kwValString::const_str() const
{
  const string clone = string(m_string.c_str());
  return clone;
}

kwValString kwValString::getType()
{
  return kwValString("kwValString");
}

const char* kwValString::c_str()
{
  return m_string.c_str();
}
