/*
 * mglCoord.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef MGLCOORD_H_
#define MGLCOORD_H_

#include "mglValue.h"
#include <iostream>

class mglValString;

class mglValCoord : public mglValue
{
public:
	mglValCoord(int x, int y, int z);
	mglValCoord(float x, float y, int z);

	mglValCoord();
	~mglValCoord();

	friend std::ostream& operator<< (std::ostream& stream, const mglValCoord& _valcoord);

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



#endif /* MGLCOORD_H_ */
