/*
 * mglMessageHandler.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#ifndef MGLMESSAGEHANDLER_H_
#define MGLMESSAGEHANDLER_H_


class mglMessageHandler
{
public:
	void processMessage(mglMessageHandler* sender, mglMessage* message);
};

#endif /* MGLMESSAGEHANDLER_H_ */
