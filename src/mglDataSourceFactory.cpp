/*
 * mglDataSourceFactory.cpp
 *
 *  Created on: 01.02.2014
 *      Author: chuhlich
 */



#include <mglSocketClient.h>
#include "mglDataSourceFactory.h"
#include "mglShm.h"
#include "mglDataContainer.h"


mglDataSourceFactory::mglDataSourceFactory()
{
}

mglDataSourceFactory::~mglDataSourceFactory()
{
}

shared_ptr<mglObject> mglDataSourceFactory::createObject(mglValString* classname, json configuration)
{
//	if (classname->str()->compare("mglShm") == 0)
//		return new mglShm(configuration);
//	if (classname->str()->compare("mglSocketClient") == 0)
//		return new mglSocketClient(configuration);
	if (classname->str()->compare("mglDataContainer") == 0)
		return shared_ptr<mglDataContainer>(new mglDataContainer(configuration));

	return NULL;
}
