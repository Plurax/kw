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
#include "nlohmann/json.hpp"
#include "api.h"

using namespace std;


/**
 * This is only a derived string object.
 *
 * The only reason to derive it is the possibility to identify its type during runtime.
 */
class DLL_PUBLIC kwValString : public kwValue<kwValString>
{
 public:
  kwValString();
  kwValString(char* _cstr);
  kwValString(const char* _cstr);
  kwValString(const string _str);
  kwValString(shared_ptr<kwValString> _str);

  DLL_PUBLIC friend std::ostream& operator<< (std::ostream& stream, const kwValString& _valstring);

  using value_type = kwValString;

  kwValString(const kwValString& right); // Copy constructor
  ~kwValString();

  void push_back(char c);
  void clear();
  const char* data();
  int size();
  bool empty() const;

  operator std::string() const { return m_string;};
    json toJson() override;
  void erase(int pos, int len);
  kwValString getType();
  kwValString asString() const override;

  kwValString operator + (const kwValString& _right);
  bool operator == (const kwValString& rhs) const;
  kwValString& operator = (const kwValString& _str);
  kwValString& operator = (const string& _str);
  bool operator < (const kwValString& _right) const;
  bool operator > (const kwValString& _right) const;

  string str();
  const string const_str() const;
  const char* c_str();

    std::shared_ptr<kwValString> getValue();
 private:
  string m_string;
  bool m_isEmpty;
};




#endif /* KWVALSTRING_H_ */
