/*
 * mglMessage.h
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#ifndef MGLMESSAGE_H_
#define MGLMESSAGE_H_

#include "mglValues/mglValString.h"


enum eMessageType
{
	mtInput = 0
};


class mglMessage
{
public:
	mglMessage(int messagetype);
	~mglMessage();

	int getMessageType();
	mglValString* m_MessageText;

	void setMessageText(mglValString& message);
	void setMessageText(const char* message);

protected:
	int m_iMessageType;

};

#endif /* MGLMESSAGE_H_ */
