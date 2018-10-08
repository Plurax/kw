/*
 * kwValFloat.h
 *
 *  Created on: 8.10.2018
 *      Author: chuhlich
 */

#ifndef KWVALFLOAT_H_
#define KWVALFLOAT_H_

#include <kw/kwValue.h>
#include <kw/kwValString.h>

class kwValFloat : public kwValue<kwValString>
{
public:

	kwValFloat();
	kwValFloat(float val);
	virtual ~kwValFloat();

	float getValue();

	friend std::ostream& operator<< (std::ostream& stream, const kwValFloat& _valfloat);

    kwValString asString();

    operator float() const;
    json toJson() override;

	bool operator >= (const kwValFloat right);
	bool operator > (const kwValFloat right);
	bool operator <= (const kwValFloat right);
	bool operator < (const kwValFloat right);
	kwValFloat& operator = (kwValFloat const& right);
	kwValFloat operator + (const kwValFloat& right);
	kwValFloat& operator += (kwValFloat const& right);
	kwValFloat operator - (const kwValFloat& right);
	kwValFloat& operator -= (kwValFloat const& right);
	kwValFloat operator * (const kwValFloat& right);
	kwValFloat operator / (const kwValFloat& right);

protected:
	float m_Value;
};

#endif /* KWVALFLOAT_H_ */
