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
#include <string>
#include <memory>

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
using namespace xercesc;



class mglDataSourceFactory
{
public:
	virtual ~mglDataSourceFactory();

	virtual mglDataSource* createDataSource(string* classname, DOMElement* configuration);
};

typedef mglDataSourceFactory* (*DataSourceCreateFunc)();
typedef void (*DataSourceDestroyFunc)(mglDataSourceFactory*);


#endif /* MGLGUIACTIONFUNCTORFACTORY_H_ */
