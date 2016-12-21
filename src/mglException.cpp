/*
 * mglException.cpp
 *
 *  Created on: 11.02.2014
 *      Author: cromas
 */


#include "mglDebug/mglTechnicalException.h"



mglTechnicalException::mglTechnicalException()
{
	m_Message = "";
}

mglTechnicalException::mglTechnicalException(unsigned int _errno, string _msg)
{
	m_ErrNo = _errno;
	m_Message = _msg;
}

mglValString mglTechnicalException::getMessage()
{
	return mglValString(m_Message.c_str());
}

