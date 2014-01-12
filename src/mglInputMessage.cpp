/*
 * mglInputMessage.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#include "mglInputMessage.h"
#include "mglCoord.h"

mglInputMessage::mglInputMessage(int messagetype)
: mglMessage(messagetype)
, m_Coord(mglCoord(0,0,0))
{

}

mglInputMessage::mglInputMessage(int messagetype, mglCoord coord, int inputtype, unsigned int mousebutton, unsigned long key)
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

mglCoord mglInputMessage::getCoord()
{
	return m_Coord;
}

void mglInputMessage::setCoord(mglCoord coord)
{
	m_Coord = coord;
}


int mglInputMessage::getInputType()
{
	return m_InputType;
}

int mglInputMessage::getMouseButton()
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

