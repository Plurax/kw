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

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace xercesc;

class mglAppConfiguration
{
public:
	void init(xercesc::DOMNode* appconfig);

	unsigned short getYRes();
	unsigned short getXRes();
	boost::posix_time::time_duration getContextAnimationDelayStart();
	boost::posix_time::time_duration getContextAnimationDelayEnd();
	bool getFullScreen();

	mglValString* getContextAnimationClass();
	mglValString* getContextAnimationLib();

private:
	unsigned short m_yres;
	unsigned short m_xres;
	/**
	 * This is a milli second value which sets the time difference for opening a context menu.
	 * The context menu can be opened by holding the touchdown or the IGR press longer than this time span.
	 */
	boost::posix_time::time_duration m_contextDelayStart;
	boost::posix_time::time_duration m_contextDelayEnd;
	bool m_FullScreen = false;
	/**
	* On windows this is a hack to allow a window which covers the complete screen, this allows composition mode with transparent background
	* We create a window which has a y resolution which is one pixel greater than the desired resolution and set its position to 0,-1
	* Therefore we can use all positions of the configuration as intendet, the 1 px row is not addressed by the code and off screen.
	*/
	bool m_OnePxAbove = false; 

	mglValString* m_ContextAnimationClass;
	mglValString* m_ContextAnimationLib;
};

#endif /* MGLAPPCONFIGURATION_H_ */
