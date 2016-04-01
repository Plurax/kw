/*
 * mglSelectionContext.cpp
 *
 *  Created on: 17.02.2014
 *      Author: cromas
 */




#include "mglGui/mglSelectionContext.h"

mglSelectionContext::mglSelectionContext()
{
	m_Focus = nullptr;
	m_pCurrentSelectionList = nullptr;
	m_Menu = nullptr;
	m_SelectListParent = nullptr;
	m_Editing = nullptr;
}
