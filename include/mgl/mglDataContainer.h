/*
 * mglDataContainer.h
 *
 *  Created on: 25.04.2014
 *      Author: chuhlich
 */

#ifndef MGLDATACONTAINER_H_
#define MGLDATACONTAINER_H_


#include "mglDataSource.h"
#include "mglValString.h"
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

#include <map>


class mglDataContainer : public mglDataSource
{
public:
	mglDataContainer(json configuration);

	void init();
	void deInit();

	void addValue(mglValString _key, shared_ptr<mglValue> _val);
	void delValue(mglValString _str);
	shared_ptr<mglValue> getValue(mglValString key);
private:
	map<mglValString, shared_ptr<mglValue>> m_MapValues;
};

#endif /* MGLDATACONTAINER_H_ */
