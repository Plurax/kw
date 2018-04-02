/*
 * kwGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWDATALAYERFACTORY_H_
#define KWDATALAYERFACTORY_H_


#include "kwObjectFactory.h"
#include "kwDataSource.h"
#include "kwLibHandle.h"
#include "kwValString.h"
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


#endif /* KWGUIACTIONFUNCTORFACTORY_H_ */
