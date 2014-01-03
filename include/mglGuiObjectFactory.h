/*
 * mglGuiObjectFactory.h
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#ifndef MGLGUIOBJECTFACTORY_H_
#define MGLGUIOBJECTFACTORY_H_

#include "../include/mglGuiObjectFactory.h"
#include "../include/mglGuiActionFunctor.h"
#include <string>
#include <memory>

#include "../include/mglGuiObject.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>



using namespace std;


class mglGuiObjectFactory
{
public:
	virtual ~mglGuiObjectFactory() {};

	virtual mglGuiObject* createGuiObject(string* classname, DOMElement* configuration);
};


typedef mglGuiObjectFactory* (*GuiFctCreateFunc)();
typedef void (*GuiObjDestroyFunc)(mglGuiObjectFactory*);

#endif /* MGLGUIOBJECTFACTORY_H_ */
