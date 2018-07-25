/*
 * kwTimer.cpp
 *
 *  Created on: 06.12.2013
 *      Author: chuhlich
 */

#include "kwTimer.h"
#include "kwDebug.h"

/*!
 * Constructor
 */
kwTimer::kwTimer()
{
  clear();
  sMode = eTimerMeasure;
}

/*!
 * Constructor with duration - will automatically set end time.
 * The timer can then be polled to check if duration is passed.
 */
kwTimer::kwTimer(boost::posix_time::time_duration _duration)
{
  m_duration = _duration;
  startCountDown();
  sMode = eTimerCountdown;
}

/**
 * Sets the new end time with the configured duration
 */
void kwTimer::startCountDown()
{
  m_endTs = (boost::posix_time::microsec_clock::local_time() + m_duration);  
}

/*!
 * Reset timer TODO
 * Set mode to up count.
 */
void kwTimer::clear()
{
  
}

/*!
 * Start the timer.
 * Sets the start time to the current local time.
 */
void kwTimer::start()
{
  m_startTs = boost::posix_time::microsec_clock::local_time();
}

/*!
 * Returns true if the Time is up and restarts the timer.
 */
bool kwTimer::doneRestart()
{
  auto now = boost::posix_time::microsec_clock::local_time();
  if (now > m_endTs)
  {
    startCountDown();
    return true;
  }
  
  return false;
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


