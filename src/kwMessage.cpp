/*
 * kwMessage.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#include "kwMessage.h"


kwMessage::kwMessage(int messagetype)
{
	m_iMessageType = messagetype;
	m_MessageText = NULL;
}


kwMessage::~kwMessage()
{
	delete m_MessageText;
}

int kwMessage::getMessageType()
{
	return m_iMessageType;
}

json kwMessage::getJsonObj()
{
  return json_obj;
}

void kwMessage::setMessageText(kwValString& message)
{
	m_MessageText = new kwValString(message);
}

void kwMessage::setMessageText(const char* message)
{
	m_MessageText = new kwValString(message);
}

kwValString* kwMessage::getMessageText()
{
	return m_MessageText;
}
