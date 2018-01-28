/*
 * kwCoord.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWCOORD_H_
#define KWCOORD_H_

#include "kwValue.h"
#include <iostream>

class kwValString;

class kwValCoord : public kwValue
{
public:
	kwValCoord(int x, int y, int z);
	kwValCoord(float x, float y, int z);

	kwValCoord();
	~kwValCoord();

	friend std::ostream& operator<< (std::ostream& stream, const kwValCoord& _valcoord);

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	void setX(int x);
	void setY(int y);
	void setZ(int z);

	bool empty();

	float m_fX;
	float m_fY;
	float m_fZ;

protected:
	bool m_isEmpty;

};



#endif /* KWCOORD_H_ */