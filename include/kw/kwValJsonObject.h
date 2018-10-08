/*
 * kwValJsonObject.h
 *
 *  Created on: 7.10.2018
 *      Author: chuhlich
 */

#ifndef KWVALJSONOBJECT_H_
#define KWVALJSONOBJECT_H_

#include <kw/kwValue.h>
#include <kw/kwValString.h>

class kwValJsonObject: public kwValue<kwValString>
{
public:

	kwValJsonObject();
	kwValJsonObject(json p_val);
	virtual ~kwValJsonObject();

	json getValue();

	friend std::ostream& operator<< (std::ostream& stream, const kwValJsonObject& _valbool);

    kwValString asString();

    json toJson() override;

protected:
	bool m_isEmpty;
	json m_Value;
};

#endif /* KWVALJSONOBJECT_H_ */
