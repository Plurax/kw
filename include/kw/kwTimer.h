/*
 * kwTimer.h
 *
 *  Created on: 06.12.2013
 *      Author: chuhlich
 */

#ifndef KWTIMER_H_
#define KWTIMER_H_

#include <boost/date_time/posix_time/posix_time.hpp>

using namespace boost::posix_time;

enum eTimerMode { eTimerMeasure, eTimerCountdown };

class kwTimer
{
public:
	void start();
	void end();
	void clear();
	bool done();
  
	kwTimer();
	kwTimer(time_duration _duration);
	void startCountDown();
	
	time_duration getDiffTime();
	time_duration getCurrentDiffTime();
private:
	ptime m_startTs;
	ptime m_endTs;
	time_duration m_duration;
	
	short sMode;
};

#endif /* KWTIMER_H_ */
