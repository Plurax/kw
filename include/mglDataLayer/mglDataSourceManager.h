/*
 * mglDataLayer.h
 *
 *  Created on: 01.02.2014
 *      Author: cromas
 */

#ifndef MGLDATALAYER_H_
#define MGLDATALAYER_H_

#include <string>
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

#include "mglDataLayer/mglDataSourceManager.h"
#include "mglDataLayer/mglDataSourceFactory.h"

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

	mglDataSource* createDataSource(string* libname, string* classname, DOMElement* configuration);

private:
	map<string, mglDataSourceFactory*> m_loadedDataSources;

};

#endif /* MGLDATALAYER_H_ */
