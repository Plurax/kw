/*
 * kwDataSource.h
 *
 *  Created on: 27.01.2014
 *      Author: chuhlich
 */

#ifndef KWDATASOURCE_H_
#define KWDATASOURCE_H_

#include "kwValString.h"
#include "kwObject.h"
#include <map>
#include <memory>

using namespace std;

/**
 * This class is a main wrapper for every data source type.
 * All objects which act as a data source should inherit from this type to allow the management by the kwSystem singleton.
 * Custom code can retrieve the data source object from the kwSystem singleton to perform any desired action.
 */
class kwDataSource : public kwObject
{
public:
	kwDataSource();
	~kwDataSource();
	virtual void init() = 0;
	virtual void deInit() = 0;
	kwDataSource(kwValString _name, unsigned int _type);
	kwValString getName();

protected:
	unsigned int m_type;
	kwValString m_name;
};

typedef map<kwValString, shared_ptr<kwDataSource>> kwDataSourceMap;


#endif /* KWDATASOURCE_H_ */