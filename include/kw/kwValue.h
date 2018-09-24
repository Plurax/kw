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

template<class T>
class kwValue : public kwObject
{
public:
    //	virtual kwValue() =0;
    virtual T asString()=0;
};

#endif /* KWVALUE_H_ */
