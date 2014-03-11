/*
 * mglTimer.cpp
 *
 *  Created on: 06.12.2013
 *      Author: cromas
 */

#include "../include/mglTimer.h"

mglTimer::mglTimer()
{
	clear();
}

void mglTimer::clear()
{
	m_startTs.tv_nsec = 0;
	m_startTs.tv_sec = 0;

	m_endTs.tv_nsec = 0;
	m_endTs.tv_sec = 0;
}

void mglTimer::start()
{
	clock_gettime(CLOCK_REALTIME, &m_startTs);
}


void mglTimer::end()
{
	clock_gettime(CLOCK_REALTIME, &m_endTs);
}

timespec mglTimer::getDiffTime()
{
	timespec temp;
	if ((m_endTs.tv_nsec - m_startTs.tv_nsec)<0)
	{
		temp.tv_sec = m_endTs.tv_sec - m_startTs.tv_sec-1;
		temp.tv_nsec = 1000000000 + m_endTs.tv_nsec - m_startTs.tv_nsec;
	} else {
		temp.tv_sec = m_endTs.tv_sec - m_startTs.tv_sec;
		temp.tv_nsec = m_endTs.tv_nsec - m_startTs.tv_nsec;
	}
	return temp;
}


timespec mglTimer::getCurrentDiffTime()
{
	timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	timespec temp;
	if ((now.tv_nsec - m_startTs.tv_nsec)<0)
	{
		temp.tv_sec = now.tv_sec - m_startTs.tv_sec-1;
		temp.tv_nsec = 1000000000 + now.tv_nsec - m_startTs.tv_nsec;
	} else {
		temp.tv_sec = now.tv_sec - m_startTs.tv_sec;
		temp.tv_nsec = now.tv_nsec - m_startTs.tv_nsec;
	}
	return temp;
}
