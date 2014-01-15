/*
 * mglInputMessage.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLINPUTMESSAGE_H_
#define MGLINPUTMESSAGE_H_

#include "mglMessage.h"
#include "mglValues/mglValCoord.h"
#include "mglGuiObject.h"

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
	mglInputMessage(int messagetype, mglValCoord coord, int inputtype, unsigned int mousebutton, unsigned long key);
	~mglInputMessage();

	mglValCoord getCoord();
	void setCoord(mglValCoord coord);

	int getInputType();
	int getMouseButton();
	void setTarget(mglGuiObject* _target);
	mglGuiObject* getTarget();

private:
	mglValCoord m_Coord;
	int m_InputType;
	unsigned int m_MouseButton;
	unsigned long m_keySym;
	mglGuiObject* m_target;
};

#endif /* MGLINPUTMESSAGE_H_ */
