/*
 * kwException.h
 *
 *  Created on: 11.02.2014
 *      Author: chuhlich
 */

#ifndef KWEXCEPTION_H_
#define KWEXCEPTION_H_

#include "kwValString.h"
#include <string>
using namespace std;

class kwTechnicalException
{
public:
	kwTechnicalException();
	kwTechnicalException(unsigned int _errno, string _msg);
	kwValString getMessage();
private:
	unsigned int m_ErrNo;
	string m_Message;
};


#endif /* KWEXCEPTION_H_ */
