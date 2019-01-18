/*
 * kwValBool.h
 *
 *  Created on: 5.10.2018
 *      Author: chuhlich
 */

#ifndef KWVALBOOL_H_
#define KWVALBOOL_H_

#include "kw/api.h"
#include <kw/kwValue.h>
#include <kw/kwValString.h>

class DLL_PUBLIC kwValBool: public kwValue<kwValString>
{
public:

	kwValBool();
	kwValBool(bool p_value);
	virtual ~kwValBool();

	bool getValue();

	DLL_PUBLIC friend std::ostream& operator<< (std::ostream& stream, const kwValBool& _valbool);

    bool operator== (const kwValBool &right) const;

    kwValString asString();

    json toJson() override;

protected:
	bool m_Value;
};

#endif /* KWVALBOOL_H_ */
