/*
 * mglSelectionContext.h
 *
 *  Created on: 17.02.2014
 *      Author: cromas
 */

#ifndef MGLSELECTIONCONTEXT_H_
#define MGLSELECTIONCONTEXT_H_

#include "mglGui/mglGuiObject.h"

/**
 * This class is the representation for the selection states in the current shown view.
 * All members are assigned from existing objects during runtime! There is no deleting destructor needed!
 */
class mglSelectionContext
{
public:
	mglSelectionContext();
	// destructor is not needed as this is only a transferobject holding pointers.

	mglGuiObject *m_SelectListParent;
	mglGuiObject *m_Menu; // This can also be every mglWindow - but it is shown via zbuffering before the mainframe

	mglGuiObjectList* m_pCurrentSelectionList;
	mglGuiObject *m_Focus; /* This pointer contains the object which holds focus in time - this is modified by
									prev/next concatenation of focussable objects by the nextfocus/prevfocus events (ie. IGR increment/decrement)
									*/
	mglGuiObject *m_Editing;
};


#endif /* MGLSELECTIONCONTEXT_H_ */
