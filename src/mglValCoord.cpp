/*
 * mglCoord.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */
#include "mglValCoord.h"
#include "mglValString.h"


mglValCoord::mglValCoord(int x, int y, int z)
{
	m_fX = (float)x;
	m_fY = (float)y;
	m_fZ = (float)z;
	m_isEmpty = false;
}

mglValCoord::mglValCoord(float x, float y, int z)
{
	m_fX = x;
	m_fY = y;
	m_fZ = z;
	m_isEmpty = false;
}

mglValCoord::mglValCoord()
{
	m_isEmpty = true;
}

mglValCoord::~mglValCoord()
{

}

std::ostream& operator<< (std::ostream& stream, const mglValCoord& _valcoord)
{
	stream << "mglValColor: { X " << _valcoord.m_fX << ", Y " << _valcoord.m_fY << ", Z " << _valcoord.m_fZ << " }";
	return stream;
}


void mglValCoord::setX(float x)
{
	m_fX = x;
}

void mglValCoord::setY(float y)
{
	m_fY = y;
}

void mglValCoord::setZ(float z)
{
	m_fZ = z;
}

void mglValCoord::setX(int x)
{
	m_fX = (float)x;
}

void mglValCoord::setY(int y)
{
	m_fY = (float)y;
}

void mglValCoord::setZ(int z)
{
	m_fZ = (float)z;
}


bool mglValCoord::empty()
{
	return m_isEmpty;
}


