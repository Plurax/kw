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

// This is the type of input! Not special keys or smth else
enum eInputType
{
	eInputMouseButtonPress,
	eInputMouseButtonRelease,
	eInputKeyPress,
	eInputKeyRelease,
	eInputMouseMove, // should be sent in time slots (every 20 ms?)
	eInputIGR
};

#define BTN_MOUSE1 1
#define BTN_MOUSE2 2
#define BTN_MOUSE3 3
#define BTN_IGR 4


class mglInputMessage : public mglMessage
{
public:
	mglInputMessage(int messagetype);
	mglInputMessage(int messagetype, mglValCoord coord, int inputtype, unsigned int mousebutton, unsigned long key);
	~mglInputMessage();

	mglValCoord getCoord();
	void setCoord(mglValCoord coord);

	int getInputType();
	int getButton();
	void setTarget(mglGuiObject* _target);
	mglGuiObject* getTarget();

	void setIGRCount(int _cnt);
	int getIGRCount();

private:
	mglValCoord m_Coord;
	int m_InputType;
	unsigned int m_MouseButton;
	unsigned long m_keySym;
	int m_iIGRCount;
	mglGuiObject* m_target;
};

#endif /* MGLINPUTMESSAGE_H_ */
