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
}

int kwMessage::getMessageType()
{
	return m_iMessageType;
}

json kwMessage::getJsonObj()
{
  return json_obj;
}

void kwMessage::setJsonObj(json obj)
{
  json_obj = obj;
}

void kwMessage::setMessageText(kwValString& message)
{
	m_MessageText = make_shared<kwValString>(message);
}

void kwMessage::setMessageText(const char* message)
{
	m_MessageText = make_shared<kwValString>(message);
}

shared_ptr<kwValString> kwMessage::getMessageText()
{
	return m_MessageText;
}
