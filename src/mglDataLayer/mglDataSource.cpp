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


mglDataSource::~mglDataSource()
{
}

mglDataSource::mglDataSource(mglValString _name, unsigned int _type)
{
	m_name = _name;
}

mglValString mglDataSource::getName()
{
	return m_name;
}

