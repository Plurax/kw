/*
 * mglAppConfiguration.h
 *
 *  Created on: 19.01.2014
 *      Author: cromas
 */

#ifndef MGLAPPCONFIGURATION_H_
#define MGLAPPCONFIGURATION_H_
#include <stdio.h>
#include <iostream>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

using namespace xercesc;

class mglAppConfiguration
{
public:
	void init(xercesc::DOMNode* appconfig);

	unsigned short getYRes();
	unsigned short getXRes();

private:
	unsigned short m_yres, m_xres;
};

#endif /* MGLAPPCONFIGURATION_H_ */
