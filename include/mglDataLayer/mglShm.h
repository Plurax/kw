/*
 * mglShm.h
 *
 *  Created on: 27.01.2014
 *      Author: cromas
 */

#ifndef MGLSHM_H_
#define MGLSHM_H_

#include "mglDataSource.h"

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

#ifdef WIN32
#else

class mglShm : public mglDataSource
{
public:
	mglShm(DOMElement* configuration);

	void init();
	void deInit();

	char* getPtr();
	bool lockSegment();
	bool unlockSegment();
	bool isLocked();
private:
#ifndef WIN32
	  key_t m_key, m_semkey;
#endif
	  int   m_shmid, m_semid, m_size;
	  char  *m_segptr;
};

#endif /* MGLSHM_H_ */
#endif