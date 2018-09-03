/*
 * kwValue.h
 *
 *  Created on: 19.02.2014
 *      Author: chuhlich
 */


#ifndef KWVALUE_H_
#define KWVALUE_H_

#include <typeinfo>
#include <iostream>
#include "kw/kwObject.h"
#include <string>

class kwValue : public kwObject
{
public:
	kwValue();
	virtual ~kwValue();
  virtual std::string asString() = 0;
};


#endif /* KWVALUE_H_ */
