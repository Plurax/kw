/*
 * kwValInteger.h
 *
 *  Created on: 26.10.2014
 *      Author: chuhlich
 */

#ifndef KWVALUES_KWVALINTEGER_H_
#define KWVALUES_KWVALINTEGER_H_

#include <kwValue.h>

class kwValInteger: public kwValue {
public:

	kwValInteger();
	kwValInteger(int val);
	virtual ~kwValInteger();

	int getValue();

	friend std::ostream& operator<< (std::ostream& stream, const kwValInteger& _valinteger);

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
	bool m_isEmpty;
	int m_Value;
};

#endif /* KWVALUES_KWVALINTEGER_H_ */
