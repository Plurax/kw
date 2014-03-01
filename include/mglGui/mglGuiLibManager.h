/*
 * mglObjectManager.h
 *
 *  Created on: 03.11.2013
 *      Author: cromas
 */

#ifndef MGLOBJECTMANAGER_H_
#define MGLOBJECTMANAGER_H_

#include "mglValues/mglValString.h"
#include <stdio.h>
#include <map>
#include <vector>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdexcept>
#include <dlfcn.h>

#include "mglGui/mglGuiObject.h"
#include "mglGui/mglGuiLibHandle.h"
#include "mglGui/mglGuiObjectFactory.h"
#include "mglGui/mglGuiActionFactory.h"
#include "mglGui/mglGuiActionLibHandle.h"

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


class mglGuiLibManager
{
public:
	~mglGuiLibManager();

	static mglGuiLibManager& Inst()
	{
		static mglGuiLibManager _instance;
		return _instance;
	};

	void init();

	mglGuiObject* createGUIObject(mglValString* libname, mglValString* classname, DOMElement* configuration);
	mglGuiActionFunctor* createGuiAction(mglValString* libname, mglValString* classname);

private:
	map<mglValString, mglGuiLibHandle*> m_loadedGuiLibraries;

	map<mglValString, mglGuiActionLibHandle*> m_loadedActionLibraries;
};


#endif /* MGLOBJECTMANAGER_H_ */
