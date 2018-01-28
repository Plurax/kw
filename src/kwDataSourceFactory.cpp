/*
 * kwDataSourceFactory.cpp
 *
 *  Created on: 01.02.2014
 *      Author: chuhlich
 */



#include <kwSocketClient.h>
#include "kwDataSourceFactory.h"
#include "kwShm.h"
#include "kwDataContainer.h"


kwDataSourceFactory::kwDataSourceFactory()
{
}

kwDataSourceFactory::~kwDataSourceFactory()
{
}

shared_ptr<kwObject> kwDataSourceFactory::createObject(kwValString* classname, json configuration)
{
//	if (classname->str()->compare("kwShm") == 0)
//		return new kwShm(configuration);
//	if (classname->str()->compare("kwSocketClient") == 0)
//		return new kwSocketClient(configuration);
	if (classname->compare("kwDataContainer") == 0)
		return shared_ptr<kwDataContainer>(new kwDataContainer(configuration));

	return NULL;
}