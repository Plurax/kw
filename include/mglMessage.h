/*
 * mglMessage.h
 *
 *  Created on: 09.11.2013
 *      Author: cromas
 */

#ifndef MGLMESSAGE_H_
#define MGLMESSAGE_H_

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

protected:
	int m_iMessageType;

};

#endif /* MGLMESSAGE_H_ */
