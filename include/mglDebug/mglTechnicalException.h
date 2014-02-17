/*
 * mglException.h
 *
 *  Created on: 11.02.2014
 *      Author: cromas
 */

#ifndef MGLEXCEPTION_H_
#define MGLEXCEPTION_H_

#include <string>

using namespace std;

class mglTechnicalException
{
public:
	mglTechnicalException();
	mglTechnicalException(unsigned int _errno, string _msg);
private:
	unsigned int m_ErrNo;
	string m_Message;
};


#endif /* MGLEXCEPTION_H_ */