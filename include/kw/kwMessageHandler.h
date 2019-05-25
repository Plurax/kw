/*
 * kwGuiActionFunctor.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWMESSAGEHANDLER_H_
#define KWMESSAGEHANDLER_H_

#include "kw/kwMessage.h"
#include <memory>
#include "kw/kwObject.h"

using namespace std;

class DLL_PUBLIC kwMessageHandler : public kwObject
{
public:
	kwMessageHandler();
	~kwMessageHandler();
	virtual shared_ptr<kwMessage> operator () (shared_ptr<kwMessage> message);
};


#endif /* KWMESSAGEHANDLER_H_ */
