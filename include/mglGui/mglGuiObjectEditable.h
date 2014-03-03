/*
 * mglGuiObjectEditable.h
 *
 *  Created on: 03.03.2014
 *      Author: cromas
 */

#ifndef MGLGUIOBJECTEDITABLE_H_
#define MGLGUIOBJECTEDITABLE_H_

#include "mglGuiObject.h"
#include "mglValues/mglValue.h"

/**
 * This class is necessary to provide functions to edit object values.
 * With this interface definition you can design own objects which can be edited by the system integrated editing
 * mechanisms with IGR and touch technologies.
 *
 * The integrated mechanisms are only used if additionally to the fit on this interface the object flag OBJ_EDITABLE is set.
 * So you can deactivate and activate editing during runtime.
 */
class mglGuiObjectEditable : public mglGuiObject
{
public:
	virtual void applyIGRCount(int _cnt);
	virtual mglValue* getIncrement(); // This is for touch (slider?) usage
	virtual void setValue(mglValue* _val);
};

#endif /* MGLGUIOBJECTEDITABLE_H_ */
