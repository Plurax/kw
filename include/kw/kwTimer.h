/*
 * kwTimer.h
 *
 *  Created on: 06.12.2013
 *      Author: chuhlich
 */

#ifndef KWTIMER_H_
#define KWTIMER_H_

#include <boost/date_time/posix_time/posix_time.hpp>

enum eTimerMode { eTimerMeasure, eTimerCountdown };

class kwTimer
{
public:
	void start();
	void end();
	void clear();
	bool done();
  
	kwTimer();
	kwTimer(boost::posix_time::time_duration _duration);

	boost::posix_time::time_duration getDiffTime();
	boost::posix_time::time_duration getCurrentDiffTime();
private:
	boost::posix_time::ptime m_startTs;
	boost::posix_time::ptime m_endTs;
	boost::posix_time::time_duration m_duration;
	
	short sMode;
};

#endif /* KWTIMER_H_ */
