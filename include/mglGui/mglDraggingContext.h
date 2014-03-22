/*
 * mglDraggingContext.h
 *
 *  Created on: 21.03.2014
 *      Author: cromas
 */

#ifndef MGLDRAGGINGCONTEXT_H_
#define MGLDRAGGINGCONTEXT_H_

#include "mglGui/mglGuiObject.h"
#include "mglValues/mglValCoord.h"

class mglDraggingContext
{
public:
	mglGuiObject* m_DraggingObject;
	mglValCoord m_StartingCoord;
	mglValCoord m_StartingObjectCoord;
};


#endif /* MGLDRAGGINGCONTEXT_H_ */
