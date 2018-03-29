/*
 * kwGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWDATASOURCEDACTORY_H_
#define KWDATASOURCEFACTORY_H_


#include "kw/kwObjectFactory.h"
#include "kw/kwDataSource.h"
#include "kw/kwLibHandle.h"
#include "kw/kwValString.h"
#include <memory>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json; 


class kwDataSourceFactory : public kwObjectFactory
{
public:
	kwDataSourceFactory();
	~kwDataSourceFactory();

	shared_ptr<kwObject> createObject(kwValString* classname, json configuration);
};

typedef kwDataSourceFactory* (*DataSourceCreateFunc)();
typedef void (*DataSourceDestroyFunc)(kwDataSourceFactory*);


#endif /* KWDATASOURCEFACTORY_H_ */
