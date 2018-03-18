/*
 * kwGuiActionFunctorFactory.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWOBJECTFACTORY_H_
#define KWOBJECTFACTORY_H_

#include "kwValString.h"
#include "kwObject.h"
#include "kwLibraryInfo.h"
#include <memory>
#include "nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;


class kwObjectFactory
{
public:
	virtual ~kwObjectFactory();
	virtual shared_ptr<kwObject> createObject(kwValString* classname, json configuration) = 0;
};


typedef kwObjectFactory* (*FctCreateFunc)();
typedef void (*FctDestroyFunc)(kwObjectFactory*);


#endif /* KWOBJECTFACTORY_H_ */
