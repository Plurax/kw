/*
 * mglValue.h
 *
 *  Created on: 19.02.2014
 *      Author: cromas
 */


#ifndef MGLVALUE_H_
#define MGLVALUE_H_

#include <typeinfo>
#include <iostream>
#include "mglObject.h"

class mglValue : public mglObject
{
public:
	mglValue();
	virtual ~mglValue();
};


#endif /* MGLVALUE_H_ */
