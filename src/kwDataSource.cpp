/*
 * kwDataSource.cpp
 *
 *  Created on: 01.02.2014
 *      Author: chuhlich
 */

#include "kwDataSource.h"


kwDataSource::kwDataSource()
{
}


kwDataSource::~kwDataSource()
{
}

kwDataSource::kwDataSource(kwValString _name, unsigned int _type)
{
	m_name = _name;
}

kwValString kwDataSource::getName()
{
	return m_name;
}

