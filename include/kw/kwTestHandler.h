/*
 * mglButtonHandler.h
 *
 *  Created on: 18.12.2013
 *      Author: chuhlich
 */

#ifndef KWTESTHANDLER_H_
#define KWTESTHANDLER_H_

#include <kw/kwMessageHandler.h>



class kwTestHandler : public kwMessageHandler
{
	public:
	kwTestHandler();

	virtual shared_ptr<kwMessage> operator () (shared_ptr<kwMessage> message);

};


#endif /* KWTESTHANDLER_H_ */
