/*
 * kwCoord.cpp
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */
#include "kwValCoord.h"
#include "kwValString.h"


kwValCoord::kwValCoord(int x, int y, int z)
{
	m_fX = (float)x;
	m_fY = (float)y;
	m_fZ = (float)z;
	m_isEmpty = false;
}

kwValCoord::kwValCoord(float x, float y, int z)
{
	m_fX = x;
	m_fY = y;
	m_fZ = z;
	m_isEmpty = false;
}

kwValCoord::kwValCoord()
{
	m_isEmpty = true;
}

kwValCoord::~kwValCoord()
{

}

std::ostream& operator<< (std::ostream& stream, const kwValCoord& _valcoord)
{
	stream << "kwValColor: { X " << _valcoord.m_fX << ", Y " << _valcoord.m_fY << ", Z " << _valcoord.m_fZ << " }";
	return stream;
}


void kwValCoord::setX(float x)
{
	m_fX = x;
}

void kwValCoord::setY(float y)
{
	m_fY = y;
}

void kwValCoord::setZ(float z)
{
	m_fZ = z;
}

void kwValCoord::setX(int x)
{
	m_fX = (float)x;
}

void kwValCoord::setY(int y)
{
	m_fY = (float)y;
}

void kwValCoord::setZ(int z)
{
	m_fZ = (float)z;
}


bool kwValCoord::empty()
{
	return m_isEmpty;
}


json kwValCoord::toJson()
{
    json j;
    return j;
}
