/*
 * mglValInteger.h
 *
 *  Created on: 26.10.2014
 *      Author: cromas
 */

#ifndef MGLVALUES_MGLVALINTEGER_H_
#define MGLVALUES_MGLVALINTEGER_H_

#include <mglValues/mglValue.h>

class mglValInteger: public mglValue {
public:
	static const enumValType m_valType = enumValType::mglValInteger;

	mglValInteger();
	mglValInteger(int val);
	virtual ~mglValInteger();

	int getValue();

	bool operator >= (const mglValInteger right);
	bool operator > (const mglValInteger right);
	bool operator <= (const mglValInteger right);
	bool operator < (const mglValInteger right);
	mglValInteger& operator = (mglValInteger const& right);
	mglValInteger operator + (const mglValInteger& right);
	mglValInteger& operator += (mglValInteger const& right);
	mglValInteger operator - (const mglValInteger& right);
	mglValInteger& operator -= (mglValInteger const& right);
	mglValInteger operator * (const mglValInteger& right);
	mglValInteger operator / (const mglValInteger& right);

	enumValType getType();

protected:
	bool m_isEmpty;
	int m_Value;
};

#endif /* MGLVALUES_MGLVALINTEGER_H_ */
