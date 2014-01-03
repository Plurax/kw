/*
 * mglCoord.cpp
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */
#include "../include/mglCoord.h"



mglCoord::mglCoord(int x, int y, int z)
{
	m_x = (float)x;
	m_y = (float)y;
	m_z = (float)z;
}

mglCoord::mglCoord(float x, float y, int z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}


mglCoord::~mglCoord()
{

}

float mglCoord::getX()
{
	return m_x;
}

float mglCoord::getY()
{
	return m_y;
}

float mglCoord::getZ()
{
	return m_z;
}


void mglCoord::setX(float x)
{
	m_x = x;
}

void mglCoord::setY(float y)
{
	m_x = y;
}

void mglCoord::setZ(float z)
{
	m_x = z;
}

void mglCoord::setX(int x)
{
	m_x = (float)x;
}

void mglCoord::setY(int y)
{
	m_x = (float)y;
}

void mglCoord::setZ(int z)
{
	m_x = (float)z;
}


