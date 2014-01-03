/*
 * mglMessage.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "../include/mglMessage.h"


mglMessage::mglMessage(int messagetype)
{
	m_iMessageType = messagetype;
}


mglMessage::~mglMessage()
{

}

int mglMessage::getMessageType()
{
	return m_iMessageType;
}
