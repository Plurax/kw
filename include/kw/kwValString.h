/*
 * kwValString.h
 *
 *  Created on: 19.02.2014
 *      Author: chuhlich
 */

#ifndef KWVALSTRING_H_
#define KWVALSTRING_H_

#include <string>
#include <memory>
#include "kw/kwValue.h"

class kwValString;

using namespace std;

/**
 * This is only a derived string object.
 *
 * The only reason to derive it is the possibility to identify its type during runtime.
 */
class kwValString : public string,kwValue
{
public:
  ~kwValString();
  kwValString();
  kwValString(char* _cstr);
  kwValString(const char* _cstr);
  kwValString(string& _str);
  kwValString(string* _str);
  kwValString(const string _str);
  kwValString(kwValString* _str);
  kwValString(shared_ptr<kwValString> _str);
  kwValString getType();
  const shared_ptr<string> const_str() const;
  kwValString(const kwValString& right); // Copy constructor

  bool empty() const;

  bool m_isEmpty;
};

#endif /* KWVALSTRING_H_ */
