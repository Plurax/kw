/*
 * mglGuiObjectFactory.h
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#ifndef MGLGUIOBJECTFACTORY_H_
#define MGLGUIOBJECTFACTORY_H_

#include <mglMessageHandler.h>
#include "mglGui/mglGuiObjectFactory.h"
#include "mglValues/mglValString.h"
#include <memory>

#include "mglGui/mglGuiObject.h"
#include "mglLibraryInfo.h"

#include <json.hpp>


using namespace std;


class mglGuiObjectFactory
{
public:
	virtual ~mglGuiObjectFactory() {};
	virtual mglLibraryInfo* getLibInfo();
	virtual shared_ptr<mglGuiObject> createGuiObject(mglValString* classname, json configuration);
	virtual void deleteGuiObject(mglGuiObject* _obj);
};


typedef mglGuiObjectFactory* (*GuiFctCreateFunc)();
typedef void (*GuiObjDestroyFunc)(mglGuiObjectFactory*);

#endif /* MGLGUIOBJECTFACTORY_H_ */
