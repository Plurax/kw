/*
 * mglGuiActionFunctor.h
 *
 *  Created on: 21.11.2013
 *      Author: cromas
 */

#ifndef MGLGUIACTIONFUNCTOR_H_
#define MGLGUIACTIONFUNCTOR_H_

#include "mglMessage.h"

class mglGuiActionFunctor
{
public:
	mglGuiActionFunctor();

	virtual mglMessage* operator () (mglMessage* message);
};


#endif /* MGLGUIACTIONFUNCTOR_H_ */
