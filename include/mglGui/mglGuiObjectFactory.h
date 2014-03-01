/*
 * mglGuiObjectFactory.h
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#ifndef MGLGUIOBJECTFACTORY_H_
#define MGLGUIOBJECTFACTORY_H_

#include "mglGui/mglGuiObjectFactory.h"
#include "mglGui/mglGuiActionFunctor.h"
#include "mglValues/mglValString.h"
#include <memory>

#include "mglGui/mglGuiObject.h"
#include "mglLibraryInfo.h"
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
	virtual mglLibraryInfo* getLibInfo();
	virtual mglGuiObject* createGuiObject(mglValString* classname, DOMElement* configuration);
};


typedef mglGuiObjectFactory* (*GuiFctCreateFunc)();
typedef void (*GuiObjDestroyFunc)(mglGuiObjectFactory*);

#endif /* MGLGUIOBJECTFACTORY_H_ */
