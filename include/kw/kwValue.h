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
#include "kwObject.h"

class kwValue : public kwObject
{
public:
	kwValue();
	virtual ~kwValue();
};


#endif /* KWVALUE_H_ */
