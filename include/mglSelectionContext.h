/*
 * mglSelectionContext.h
 *
 *  Created on: 17.02.2014
 *      Author: cromas
 */

#ifndef MGLSELECTIONCONTEXT_H_
#define MGLSELECTIONCONTEXT_H_

#include "mglGui/mglGuiObject.h"


class mglSelectionContext
{
public:
	mglSelectionContext();
	// destructor is not needed as this is only a transferobject holding pointers.

	mglGuiObject *m_CurrentMainFrame;
	mglGuiObject *m_SelectListParent;
	mglGuiObject *m_CurrentMenu; // This can also be every mglWindow - but it is shown via zbuffering before the mainframe

	mglGuiObjectList* m_pCurrentSelectionList;
	mglGuiObject *m_CurrentFocus; /* This pointer contains the object which holds focus in time - this is modified by
									prev/next concatenation of focussable objects by the nextfocus/prevfocus events (ie. IGR increment/decrement)
									*/
};


#endif /* MGLSELECTIONCONTEXT_H_ */
