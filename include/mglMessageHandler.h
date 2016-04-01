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

using namespace std;

class mglMessageHandler
{
public:
	mglMessageHandler();

	virtual shared_ptr<mglMessage> operator () (shared_ptr<mglMessage> message);
};


#endif /* MGLMESSAGEHANDLER_H_ */
