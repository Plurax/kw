/*
 * mglInputMessage.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLINPUTMESSAGE_H_
#define MGLINPUTMESSAGE_H_

#include "mglMessage.h"
#include "mglCoord.h"

enum eInputType
{
	eInputMouseButtonPress,
	eInputMouseButtonRelease,
	eInputKeyPress,
	eInputKeyRelease,
	eInputMouseMove // should be sent in time slots (every 20 ms?)
};

class mglInputMessage : public mglMessage
{
public:
	mglInputMessage(int messagetype);
	mglInputMessage(int messagetype, mglCoord coord, int inputtype, unsigned int mousebutton, unsigned long key);
	~mglInputMessage();

	mglCoord getCoord();
	void setCoord(mglCoord coord);

	int getInputType();
	int getMouseButton();

private:
	mglCoord m_Coord;
	int m_InputType;
	unsigned int m_MouseButton;
	unsigned long m_keySym;
};

#endif /* MGLINPUTMESSAGE_H_ */
