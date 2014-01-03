/*
 * mglTimer.cpp
 *
 *  Created on: 06.12.2013
 *      Author: cromas
 */

#include "../include/mglTimer.h"


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
