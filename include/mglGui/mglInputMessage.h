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
#include <boost/date_time/posix_time/posix_time.hpp>

// This is the type of input! Not special keys or smth else
enum eInputType
{
	eInputMouseButtonPress,
	eInputMouseButtonRelease,
	eInputKeyPress,
	eInputKeyRelease,
	eInputTimedRefresh, // is used for context menu opening - no move but already mouse/IGR down... send cyclic events!
	eInputMouseMove, // should be sent in time slots (every 20 ms?)
	eInputIGR, // This is the IGR increment or decrement!
	eInputIGRPress, // this is the IGR button
	eInputIGRRelease, // this is the IGR button
	eEditorInput // If an editor window is openened - this event is used to inform the editede object about modifications
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

	void setDiffTime(boost::posix_time::time_duration _tspec);
	boost::posix_time::time_duration getDiffTime();

	void setContextTimeEnd(bool flag);
	bool getContextTimeEnd();

	void setEditedObject(mglGuiObject* _edited);
	mglGuiObject* getEditedObject();

	float getDragDeltaX();
	void setDragDeltaX(float _deltax);
	float getDragDeltaY();
	void setDragDeltaY(float _deltay);
private:
	mglValCoord m_Coord;
	int m_InputType;
	unsigned int m_MouseButton;
	unsigned long m_keySym;
	int m_iIGRCount;
	mglGuiObject* m_target;
	boost::posix_time::time_duration m_DiffTime;
	bool m_ContextAnimationCompleted;
	mglGuiObject* m_EditedObject;

	float m_fDragDeltaX;
	float m_fDragDeltaY;
};

#endif /* MGLINPUTMESSAGE_H_ */
