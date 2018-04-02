/*
 * kwDataContainer.h
 *
 *  Created on: 25.04.2014
 *      Author: chuhlich
 */

#ifndef KWDATACONTAINER_H_
#define KWDATACONTAINER_H_


#include "kwDataSource.h"
#include "kwValString.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

#include <map>


class kwDataContainer : public kwDataSource
{
public:
	kwDataContainer(json configuration);

	void init();
	void deInit();

	void addValue(kwValString _key, shared_ptr<kwValue> _val);
	void delValue(kwValString _str);
	shared_ptr<kwValue> getValue(kwValString key);
private:
	map<kwValString, shared_ptr<kwValue>> m_MapValues;
};

#endif /* KWDATACONTAINER_H_ */
