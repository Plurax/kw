/*
 * mglValString.h
 *
 *  Created on: 19.02.2014
 *      Author: cromas
 */

#ifndef MGLVALSTRING_H_
#define MGLVALSTRING_H_

#include <string>
#include <iostream>
#include "mglValue.h"



using namespace std;

/**
 * This is only a derived string object.
 *
 * The only reason to derive it is the possibility to identify its type during runtime.
 */
class mglValString
{
public:
	  static const mglValType m_valType = mglValType::mglValString;

	  mglValString();
	  mglValString(char* _cstr);
	  mglValString(const char* _cstr);
	  mglValString(string& _str);
	  mglValString(string* _str);
	  mglValString(const string _str);

	  mglValString(const mglValString& right); // Copy constructor
	  ~mglValString();

	  int size();
	  bool empty();


	  mglValString operator + (const mglValString& _right);
	  bool operator == (const mglValString& _right);
	  mglValString& operator = (mglValString& _str);
	  bool operator < (const mglValString& _right) const;

	  const string* str() const;
private:
	  string* m_string;
	  bool m_isEmpty;
};


#endif /* MGLVALSTRING_H_ */
