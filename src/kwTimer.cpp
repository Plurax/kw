/*
 * kwTimer.cpp
 *
 *  Created on: 06.12.2013
 *      Author: chuhlich
 */

#include "kwTimer.h"

/*!
 * Constructor
 */
kwTimer::kwTimer()
{
	clear();
}

/*!
 * Reset timer TODO
 */
void kwTimer::clear()
{
// Todo: Necessary?
}

/*!
 * Start the timer.
 */
void kwTimer::start()
{
	m_startTs = boost::posix_time::microsec_clock::local_time();
}

/*!
 * End the timer.
 */
void kwTimer::end()
{
	m_endTs = boost::posix_time::microsec_clock::local_time();
}

/*!
 * Get the difftime of the timer after it ended.
 */
boost::posix_time::time_duration kwTimer::getDiffTime()
{
	boost::posix_time::time_duration temp;
	return m_endTs - m_startTs;
}


/*!
 * Get the difftime of the timer in relation to current time.
 */
boost::posix_time::time_duration kwTimer::getCurrentDiffTime()
{
	boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
	return now - m_startTs;
}
