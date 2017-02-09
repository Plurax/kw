/*
 * mglMessage.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#include "mglMessage.h"


mglMessage::mglMessage(int messagetype)
{
	m_iMessageType = messagetype;
	m_MessageText = NULL;
}


mglMessage::~mglMessage()
{
	delete m_MessageText;
}

int mglMessage::getMessageType()
{
	return m_iMessageType;
}


void mglMessage::setMessageText(mglValString& message)
{
	m_MessageText = new mglValString(message);
}

void mglMessage::setMessageText(const char* message)
{
	m_MessageText = new mglValString(message);
}

mglValString* mglMessage::getMessageText()
{
	return m_MessageText;
}
