/*
 * mglInputMessage.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "mglGui/mglInputMessage.h"
#include "mglValues/mglValCoord.h"

mglInputMessage::mglInputMessage(int messagetype)
: mglMessage(messagetype)
, m_Coord(mglValCoord(0,0,0))
{

}

mglInputMessage::mglInputMessage(int messagetype, mglValCoord coord, int inputtype, unsigned int mousebutton, unsigned long key)
: mglMessage(messagetype)
, m_Coord(coord)
{
	m_Coord = coord;
	m_InputType = inputtype;
	m_keySym = key;
	m_MouseButton = mousebutton;
	m_target = NULL;
}

mglInputMessage::~mglInputMessage()
{

}

mglValCoord mglInputMessage::getCoord()
{
	return m_Coord;
}

void mglInputMessage::setCoord(mglValCoord coord)
{
	m_Coord = coord;
}


int mglInputMessage::getInputType()
{
	return m_InputType;
}

int mglInputMessage::getButton()
{
	return m_MouseButton;
}

void mglInputMessage::setTarget(mglGuiObject* _target)
{
	m_target = _target;
}


mglGuiObject* mglInputMessage::getTarget()
{
	return m_target;
}


void mglInputMessage::setIGRCount(int _cnt)
{
	m_iIGRCount = _cnt;
}

int mglInputMessage::getIGRCount()
{
	return m_iIGRCount;
}

