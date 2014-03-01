/*
 * mglDataSource.cpp
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */

#include "mglDataLayer/mglDataSource.h"


mglDataSource::mglDataSource()
{
}

mglDataSource::mglDataSource(mglValString _name, unsigned int _type)
{
	m_name = _name;
	m_type = _type;
}

mglValString mglDataSource::getName()
{
	return m_name;
}

unsigned int mglDataSource::getType()
{
	return m_type;
}
