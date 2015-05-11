/*
 * mglDataLayer.h
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */

#ifndef MGLDATALAYER_H_
#define MGLDATALAYER_H_

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

#ifdef WIN32
#include "Windows.h"
#else
#include <dlfcn.h>
#endif

#include "mglDataLayer/mglDataSourceManager.h"
#include "mglDataLayer/mglDataSourceFactory.h"
#include "mglDataLayer/mglDataLibHandle.h"


#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

using namespace xercesc;

class mglDataSourceManager
{
public:
	~mglDataSourceManager();

	static mglDataSourceManager& Inst()
	{
		static mglDataSourceManager _instance;
		return _instance;
	};

	void init();

	mglDataSource* createDataSource(mglValString* libname, mglValString* classname, DOMElement* configuration);

private:
	map<mglValString, mglDataLibHandle*> m_loadedDataSources;

};

#endif /* MGLDATALAYER_H_ */
