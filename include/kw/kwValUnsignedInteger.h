/*
 * kwValInteger.h
 *
 *  Created on: 26.10.2014
 *      Author: chuhlich
 */

#ifndef KWVALUNSIGNEDINTEGER_H_
#define KWVALUNSIGNEDINTEGER_H_

#include <kw/kwValue.h>
#include <kw/kwValString.h>

class kwValUnsignedInteger: public kwValue<kwValString>
{
public:

	kwValUnsignedInteger();
	kwValUnsignedInteger(uint val);
	virtual ~kwValUnsignedInteger();

	uint getValue();

	friend std::ostream& operator<< (std::ostream& stream, const kwValUnsignedInteger& _valinteger);

    kwValString asString();

    operator uint() const;
    json toJson() override;

	bool operator >= (const kwValUnsignedInteger right);
	bool operator > (const kwValUnsignedInteger right);
	bool operator <= (const kwValUnsignedInteger right);
	bool operator < (const kwValUnsignedInteger right);
	kwValUnsignedInteger& operator = (kwValUnsignedInteger const& right);
	kwValUnsignedInteger operator + (const kwValUnsignedInteger& right);
	kwValUnsignedInteger& operator += (kwValUnsignedInteger const& right);
	kwValUnsignedInteger operator - (const kwValUnsignedInteger& right);
	kwValUnsignedInteger& operator -= (kwValUnsignedInteger const& right);
	kwValUnsignedInteger operator * (const kwValUnsignedInteger& right);
	kwValUnsignedInteger operator / (const kwValUnsignedInteger& right);

protected:
	bool m_isEmpty;
	uint m_Value;
};

#endif /* KWVALUNSIGNEDINTEGER_H_ */
