/*
 * mglGuiObjectFactory.cpp
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#include "../include/mglGuiObjectFactory.h"
#include <stdio.h>


/*
 * For the first time the standard object factory can only return mglWindow!
 */
mglGuiObject* mglGuiObjectFactory::createGuiObject(string* classname, DOMElement* configuration)
{
	if (classname->compare("mglGuiObject") == 0)
		return new mglGuiObject(configuration);

	return NULL;
}


