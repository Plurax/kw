/*
 * mglDataContainer.h
 *
 *  Created on: 25.04.2014
 *      Author: cromas
 */

#ifndef MGLDATACONTAINER_H_
#define MGLDATACONTAINER_H_


#include "mglDataSource.h"
#include "mglValues/mglValString.h"

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

#include <map>


class mglDataContainer : public mglDataSource
{
public:
	mglDataContainer(DOMElement* configuration);

	void init();
	void deInit();

	void addValue(mglValString _key, mglValue* _val);
	void delValue(mglValString _str);
	mglValue* getValue(mglValString key);
private:
	map<mglValString, mglValue*> m_MapValues;
};

#endif /* MGLDATACONTAINER_H_ */
