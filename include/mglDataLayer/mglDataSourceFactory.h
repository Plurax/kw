/*
 * mglGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLDATALAYERFACTORY_H_
#define MGLDATALAYERFACTORY_H_


#include "mglDataLayer/mglDataSourceFactory.h"
#include "mglDataLayer/mglDataSource.h"
#include "mglLibHandle.h"
#include "mglValues/mglValString.h"
#include <memory>
#include <json.hpp>

using namespace std;
using json = nlohmann::json; 


class mglDataSourceFactory
{
public:
	virtual ~mglDataSourceFactory();

	virtual shared_ptr<mglDataSource> createDataSource(mglValString* classname, json configuration);
};

typedef mglDataSourceFactory* (*DataSourceCreateFunc)();
typedef void (*DataSourceDestroyFunc)(mglDataSourceFactory*);


#endif /* MGLGUIACTIONFUNCTORFACTORY_H_ */
