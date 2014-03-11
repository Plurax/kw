/*
 * mglTimer.h
 *
 *  Created on: 06.12.2013
 *      Author: cromas
 */

#ifndef MGLTIMER_H_
#define MGLTIMER_H_

#include <time.h>

class mglTimer
{
public:
	void start();
	void end();
	void clear();

	mglTimer();

	timespec getDiffTime();
	timespec getCurrentDiffTime();
private:
	timespec m_startTs;
	timespec m_endTs;

};

#endif /* MGLTIMER_H_ */
