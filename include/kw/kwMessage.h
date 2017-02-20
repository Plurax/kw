/*
 * kwMessage.h
 *
 *  Created on: 09.11.2013
 *      Author: chuhlich
 */

#ifndef KWMESSAGE_H_
#define KWMESSAGE_H_

#include "kwValString.h"
#include "kwObject.h"

enum eMessageType
{
	mtInput = 0
};


class kwMessage : public kwObject
{
public:
	kwMessage(int messagetype);
	virtual ~kwMessage();

	int getMessageType();

	void setMessageText(kwValString& message);
	void setMessageText(const char* message);

	kwValString* getMessageText();

protected:
	int m_iMessageType;
	kwValString* m_MessageText;

};

#endif /* KWMESSAGE_H_ */
