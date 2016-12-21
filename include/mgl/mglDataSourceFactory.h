/*
 * mglGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLDATALAYERFACTORY_H_
#define MGLDATALAYERFACTORY_H_


#include "mglObjectFactory.h"
#include "mglDataLayer/mglDataSource.h"
#include "mglLibHandle.h"
#include "mglValues/mglValString.h"
#include <memory>
#include <json.hpp>

using namespace std;
using json = nlohmann::json; 


class mglDataSourceFactory : public mglObjectFactory
{
public:
	mglDataSourceFactory();
	~mglDataSourceFactory();

	shared_ptr<mglObject> createObject(mglValString* classname, json configuration);
};

typedef mglDataSourceFactory* (*DataSourceCreateFunc)();
typedef void (*DataSourceDestroyFunc)(mglDataSourceFactory*);


#endif /* MGLGUIACTIONFUNCTORFACTORY_H_ */