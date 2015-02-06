/*
 * mglGuiActionFunctor.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLACTIONFUNCTOR_H_
#define MGLACTIONFUNCTOR_H_

#include "mglMessage.h"

class mglActionFunctor
{
public:
	mglActionFunctor();

	virtual mglMessage* operator () (mglMessage* message);
};


#endif /* MGLACTIONFUNCTOR_H_ */
