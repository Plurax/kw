/*
 * mglDataSourceFactory.cpp
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */



#include "mglDataLayer/mglDataSourceFactory.h"
#include "mglDataLayer/mglShm.h"

mglDataSourceFactory::~mglDataSourceFactory()
{
}

mglDataSource* mglDataSourceFactory::createDataSource(string* classname, DOMElement* configuration)
{
	if (classname->compare("mglShm") == 0)
		return new mglShm(configuration);

	return NULL;
}
