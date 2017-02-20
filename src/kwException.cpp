/*
 * kwException.cpp
 *
 *  Created on: 11.02.2014
 *      Author: chuhlich
 */


#include "kwTechnicalException.h"



kwTechnicalException::kwTechnicalException()
{
	m_Message = "";
}

kwTechnicalException::kwTechnicalException(unsigned int _errno, string _msg)
{
	m_ErrNo = _errno;
	m_Message = _msg;
}

kwValString kwTechnicalException::getMessage()
{
	return kwValString(m_Message.c_str());
}

