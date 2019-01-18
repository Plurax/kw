/*
 * kwValInteger.h
 *
 *  Created on: 26.10.2014
 *      Author: chuhlich
 */

#ifndef KWVALINTEGER_H_
#define KWVALINTEGER_H_

#include <kw/api.h>
#include <kw/kwValue.h>
#include <kw/kwValString.h>

class DLL_PUBLIC kwValInteger: public kwValue<kwValString>
{
public:

	kwValInteger();
	kwValInteger(int val);
	virtual ~kwValInteger();

	int getValue();

	friend DLL_PUBLIC std::ostream& operator<< (std::ostream& stream, const kwValInteger& _valinteger);

    kwValString asString();

    operator int() const;
    json toJson() override;

	bool operator == (const kwValInteger right);
	bool operator != (const kwValInteger right);
	bool operator >= (const kwValInteger right);
	bool operator > (const kwValInteger right);
	bool operator <= (const kwValInteger right);
	bool operator < (const kwValInteger right);
	kwValInteger& operator = (kwValInteger const& right);
	kwValInteger operator + (const kwValInteger& right);
	kwValInteger& operator += (kwValInteger const& right);
	kwValInteger operator - (const kwValInteger& right);
	kwValInteger& operator -= (kwValInteger const& right);
	kwValInteger operator * (const kwValInteger& right);
	kwValInteger operator / (const kwValInteger& right);

protected:
	int m_Value;
};

#endif /* KWVALINTEGER_H_ */
