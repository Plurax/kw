/*
 * mglGuiActionFunctor.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLMESSAGEHANDLER_H_
#define MGLMESSAGEHANDLER_H_

#include "mglMessage.h"

class mglMessageHandler
{
public:
	mglMessageHandler();

	virtual mglMessage* operator () (mglMessage* message);
};


#endif /* MGLMESSAGEHANDLER_H_ */
