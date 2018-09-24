/*
 * kwDataSource.cpp
 *
 *  Created on: 01.02.2014
 *      Author: chuhlich
 */

#include "kwDataSource.h"
#include "kwValInteger.h"


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

shared_ptr<kwValue<kwValString>> kwDataSource::getValue(kwValString key)
{
    return std::make_shared<kwValInteger>(42);
}

