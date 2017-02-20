/*
 * kwGuiActionFunctor.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWMESSAGEHANDLER_H_
#define KWMESSAGEHANDLER_H_

#include "kwMessage.h"
#include <memory>
#include "kwObject.h"

using namespace std;

class kwMessageHandler : public kwObject
{
public:
	kwMessageHandler();
	~kwMessageHandler();
	virtual shared_ptr<kwMessage> operator () (shared_ptr<kwMessage> message);
};


#endif /* KWMESSAGEHANDLER_H_ */
