/*
 * mglTimer.h
 *
 *  Created on: 06.12.2013
 *      Author: chuhlich
 */

#ifndef MGLTIMER_H_
#define MGLTIMER_H_

#include <boost/date_time/posix_time/posix_time.hpp>


class mglTimer
{
public:
	void start();
	void end();
	void clear();

	mglTimer();

	boost::posix_time::time_duration getDiffTime();
	boost::posix_time::time_duration getCurrentDiffTime();
private:
	boost::posix_time::ptime m_startTs;
	boost::posix_time::ptime m_endTs;

};

#endif /* MGLTIMER_H_ */
