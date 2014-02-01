/*
 * mglDataSource.h
 *
 *  Created on: 27.01.2014
 *      Author: cromas
 */

#ifndef MGLDATASOURCE_H_
#define MGLDATASOURCE_H_

#include <string>
#include <map>

using namespace std;

/**
 * This class is a main wrapper for every data source type.
 * All objects which act as a data source should inherit from this type to allow the management by the mglSystem singleton.
 * Custom code can retrieve the data source object from the mglSystem singleton to perform any desired action.
 */
class mglDataSource
{
public:
	mglDataSource();
	virtual void init() = 0;
	virtual void deInit() = 0;
	mglDataSource(string _name, unsigned int _type);
	string getName();
	unsigned int getType();

protected:
	unsigned int m_type;
	string m_name;
};

typedef map<string,mglDataSource*> mglDataSourceMap;


#endif /* MGLDATASOURCE_H_ */
