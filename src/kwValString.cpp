/*
 * kwValString.cpp
 *
 *  Created on: 28.02.2014
 *      Author: chuhlich
 */


#include <string.h>
#include <stdio.h>
#include "kwValString.h"

using namespace std;


kwValString::kwValString() : string()
{
}


kwValString::kwValString(char* _cstr) : string(_cstr)
{
  m_isEmpty = false;
}


kwValString::kwValString(const char* _cstr) : string(_cstr)
{
  m_isEmpty = false;
}


kwValString::kwValString(string& _str) : string(_str)
{
  m_isEmpty = false;
}


kwValString::kwValString(string* _str) : string(*_str)
{
  m_isEmpty = false;
}


kwValString::kwValString(const string _str) : string(_str)
{
  m_isEmpty = false;
}


kwValString::kwValString(kwValString*_str) : string(*_str)
{
  m_isEmpty = false;
}

kwValString::kwValString(shared_ptr<kwValString> _str) : string(*_str)
{
  m_isEmpty = false;
}

// Copy constructor
kwValString::kwValString(const kwValString& right) : string(right)
{
  m_isEmpty = false;
}


kwValString::~kwValString()
{
}


bool kwValString::empty() const
{
  return m_isEmpty;
}


const shared_ptr<string> kwValString::const_str() const
{
  const shared_ptr<string> clone = make_shared<string>(this->c_str());
  return clone;
}

kwValString kwValString::getType()
{
  return kwValString("kwValString");
}
