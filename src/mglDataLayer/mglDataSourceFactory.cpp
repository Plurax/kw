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

mglDataSource* mglDataSourceFactory::createDataSource(mglValString* classname, DOMElement* configuration)
{
	if (classname->str()->compare("mglShm") == 0)
		return new mglShm(configuration);

	return NULL;
}
