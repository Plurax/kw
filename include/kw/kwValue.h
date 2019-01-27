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
#include "nlohmann/json.hpp"
using json = nlohmann::json;

template<class T>
class kwValue : public kwObject
{
public:
    //	virtual kwValue() =0;
    virtual T asString() const = 0;
    virtual json toJson() = 0;
};

#endif /* KWVALUE_H_ */
