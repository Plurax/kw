/*
 * mglGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLOBJECTFACTORY_H_
#define MGLOBJECTFACTORY_H_

#include "mglValues/mglValString.h"
#include "mglObject.h"
#include "mglLibraryInfo.h"
#include <memory>
#include "json.hpp"


using namespace std;
using json = nlohmann::json;


class mglObjectFactory
{
public:
	virtual ~mglObjectFactory();
	virtual shared_ptr<mglObject> createObject(mglValString* classname, json configuration) = 0;
};


typedef mglObjectFactory* (*FctCreateFunc)();
typedef void (*FctDestroyFunc)(mglObjectFactory*);


#endif /* MGLOBJECTFACTORY_H_ */
