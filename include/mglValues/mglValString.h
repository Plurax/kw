/*
 * mglValString.h
 *
 *  Created on: 19.02.2014
 *      Author: cromas
 */

#ifndef MGLVALSTRING_H_
#define MGLVALSTRING_H_

#include <string>
#include "mglValues/mglValue.h"

using namespace std;

/**
 * This is only a derived string object.
 *
 * The only reason to derive it is the possibility to identify its type during runtime.
 */
class mglValString : std::string
{
	  static const mglValType m_valType = mglValType::mglValString;
};


#endif /* MGLVALSTRING_H_ */
