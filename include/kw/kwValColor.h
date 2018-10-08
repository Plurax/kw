/*
 * kwColor.h
 *
 *  Created on: 09.11.2013
 *      Author: chuhlich
 */

#ifndef KWVALCOLOR_H_
#define KWVALCOLOR_H_


#include "kw/kwValString.h"
#include "kw/kwValue.h"

class kwValColor : public kwValue<kwValString>
{
public:
	kwValColor();
	~kwValColor();
	kwValColor(float red, float green, float blue, float alpha);
	kwValColor(const char* hex);

	friend std::ostream& operator<< (std::ostream& stream, const kwValColor& _valcolor);

    json toJson() override;
    kwValString asString();
	kwValString getType();

	float fRed;
	float fGreen;
	float fBlue;
	float fAlpha;

private:
	static const kwValString m_valType;
};

#endif /* KWVALCOLOR_H_ */
