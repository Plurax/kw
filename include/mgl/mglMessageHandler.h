/*
 * mglGuiActionFunctor.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLMESSAGEHANDLER_H_
#define MGLMESSAGEHANDLER_H_

#include "mglMessage.h"
#include <memory>
#include "mglObject.h"

using namespace std;

class mglMessageHandler : public mglObject
{
public:
	mglMessageHandler();
	~mglMessageHandler();
	virtual shared_ptr<mglMessage> operator () (shared_ptr<mglMessage> message);
};


#endif /* MGLMESSAGEHANDLER_H_ */