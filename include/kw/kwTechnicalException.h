/*
 * kwException.h
 *
 *  Created on: 11.02.2014
 *      Author: chuhlich
 */

#ifndef KWTECHNICALEXCEPTION_H_
#define KWTECHNICALEXCEPTION_H_

#include "kw/kwValString.h"
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


#endif /* KWTECHNICALEXCEPTION_H_ */
