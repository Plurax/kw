/*
 * kwCoord.h
 *
 *  Created on: 21.11.2013
 *      Author: chuhlich
 */

#ifndef KWVALCOORD_H_
#define KWVALCOORD_H_

#include "kw/kwValue.h"
#include <iostream>

class kwValString;

class kwValCoord : public kwValue<kwValString>
{
public:
	kwValCoord(int x, int y, int z);
	kwValCoord(float x, float y, int z);

	kwValCoord();
	~kwValCoord();

	friend std::ostream& operator<< (std::ostream& stream, const kwValCoord& _valcoord);
    json toJson() override;

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



#endif /* KWVALCOORD_H_ */
