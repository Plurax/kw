/*
 * mglValString.h
 *
 *  Created on: 19.02.2014
 *      Author: cromas
 */

#ifndef MGLVALSTRING_H_
#define MGLVALSTRING_H_

#include <string>
#include "mglValue.h"

class mglValString;

using namespace std;

/**
 * This is only a derived string object.
 *
 * The only reason to derive it is the possibility to identify its type during runtime.
 */
class mglValString : public mglValue
{
public:
	  mglValString();
	  mglValString(char* _cstr);
	  mglValString(const char* _cstr);
	  mglValString(string& _str);
	  mglValString(string* _str);
	  mglValString(const string _str);
	  mglValString(mglValString*_str);

	  friend std::ostream& operator<< (std::ostream& stream, const mglValString& _valstring);

	  mglValString(const mglValString& right); // Copy constructor
	  ~mglValString();

	  int size();
	  bool empty();

	  void erase(int pos, int len);
	  mglValString getType();

	  mglValString operator + (const mglValString& _right);
	  bool operator == (const mglValString& _right);
	  mglValString& operator = (const mglValString& _str);
	  bool operator < (const mglValString& _right) const;

	  const string* str() const;
private:
	  string* m_string;
	  bool m_isEmpty;
};


#endif /* MGLVALSTRING_H_ */
