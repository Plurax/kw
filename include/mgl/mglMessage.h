/*
 * mglMessage.h
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#ifndef MGLMESSAGE_H_
#define MGLMESSAGE_H_

#include "mglValues/mglValString.h"
#include "mglObject.h"

enum eMessageType
{
	mtInput = 0
};


class mglMessage : public mglObject
{
public:
	mglMessage(int messagetype);
	virtual ~mglMessage();

	int getMessageType();

	void setMessageText(mglValString& message);
	void setMessageText(const char* message);

	mglValString* getMessageText();

protected:
	int m_iMessageType;
	mglValString* m_MessageText;

};

#endif /* MGLMESSAGE_H_ */