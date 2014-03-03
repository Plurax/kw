/*
 * mglCoord.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLCOORD_H_
#define MGLCOORD_H_

#include "mglValue.h"

class mglValCoord : public mglValue
{
public:
  static const mglValType m_valType = mglValType::mglValCoord;
	mglValCoord(int x, int y, int z);
	mglValCoord(float x, float y, int z);

	~mglValCoord();

	mglValType getType();

	float getX();
	float getY();
	float getZ();

	void setX(float x);
	void setY(float y);
	void setZ(float z);

	void setX(int x);
	void setY(int y);
	void setZ(int z);

protected:
	float m_x;
	float m_y;
	float m_z;
};



#endif /* MGLCOORD_H_ */
