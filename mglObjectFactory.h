/*
 * mglObjectFactory.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */

#ifndef MGLOBJECTFACTORY_H_
#define MGLOBJECTFACTORY_H_


class mglObjectFactory
{
public:
	mglObjectFactory();

	mglWindow* create2dObject(std::string classname);
	bool delete2dObject(mglWindow*);


private:

};

#endif /* MGLOBJECTFACTORY_H_ */
