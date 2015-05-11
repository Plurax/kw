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
// Todo: Necessary?
}

void mglTimer::start()
{
	m_startTs = boost::posix_time::microsec_clock::local_time();
}


void mglTimer::end()
{
	m_endTs = boost::posix_time::microsec_clock::local_time();
}

boost::posix_time::time_duration mglTimer::getDiffTime()
{
	boost::posix_time::time_duration temp;
	return m_endTs - m_startTs;
}


boost::posix_time::time_duration mglTimer::getCurrentDiffTime()
{
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	return now - m_startTs;
}
