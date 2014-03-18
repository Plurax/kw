/*
 * mglCoord.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */
#include "../include/mglValues/mglValCoord.h"



mglValCoord::mglValCoord(int x, int y, int z)
{
	m_x = (float)x;
	m_y = (float)y;
	m_z = (float)z;
}

mglValCoord::mglValCoord(float x, float y, int z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

mglValCoord::mglValCoord()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
}

mglValCoord::~mglValCoord()
{

}

float mglValCoord::getX()
{
	return m_x;
}

float mglValCoord::getY()
{
	return m_y;
}

float mglValCoord::getZ()
{
	return m_z;
}


void mglValCoord::setX(float x)
{
	m_x = x;
}

void mglValCoord::setY(float y)
{
	m_x = y;
}

void mglValCoord::setZ(float z)
{
	m_x = z;
}

void mglValCoord::setX(int x)
{
	m_x = (float)x;
}

void mglValCoord::setY(int y)
{
	m_x = (float)y;
}

void mglValCoord::setZ(int z)
{
	m_x = (float)z;
}

mglValType mglValCoord::getType()
{
	return m_valType;
}

