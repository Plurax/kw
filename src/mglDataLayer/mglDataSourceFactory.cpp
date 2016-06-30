/*
 * mglDataSourceFactory.cpp
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */



#include <mglDataLayer/mglSocketClient.h>
#include "mglDataLayer/mglDataSourceFactory.h"
#include "mglDataLayer/mglShm.h"
#include "mglDataLayer/mglDataContainer.h"

mglDataSourceFactory::~mglDataSourceFactory()
{
}

shared_ptr<mglDataSource> mglDataSourceFactory::createDataSource(mglValString* classname, json configuration)
{
//	if (classname->str()->compare("mglShm") == 0)
//		return new mglShm(configuration);
//	if (classname->str()->compare("mglSocketClient") == 0)
//		return new mglSocketClient(configuration);
	if (classname->str()->compare("mglDataContainer") == 0)
		return shared_ptr<mglDataContainer>(new mglDataContainer(configuration));

	return NULL;
}
