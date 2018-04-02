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
#include "kwValue.h"

class kwValString;

using namespace std;

/**
 * This is only a derived string object.
 *
 * The only reason to derive it is the possibility to identify its type during runtime.
 */
class kwValString : public kwValue
{
public:
	  kwValString();
	  kwValString(char* _cstr);
	  kwValString(const char* _cstr);
	  kwValString(string& _str);
	  kwValString(string* _str);
	  kwValString(const string _str);
	  kwValString(kwValString* _str);
	  kwValString(shared_ptr<kwValString> _str);

	  friend std::ostream& operator<< (std::ostream& stream, const kwValString& _valstring);

	  kwValString(const kwValString& right); // Copy constructor
	  ~kwValString();

	  int size();
	  bool empty() const;

	  void erase(int pos, int len);
	  kwValString getType();

	  kwValString operator + (const kwValString& _right);
	  bool operator == (const kwValString& _right);
	  kwValString& operator = (const kwValString& _str);
	  bool operator < (const kwValString& _right) const;

	  shared_ptr<string> str();
	  const shared_ptr<string> const_str() const;
	  const char* c_str();

 private:
	  shared_ptr<string> m_string;
	  bool m_isEmpty;
};


#endif /* KWVALSTRING_H_ */
