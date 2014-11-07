/*
 * mglDataContainer.cpp
 *
 *  Created on: 25.04.2014
 *      Author: cromas
 */


#include "mglDataLayer/mglDataContainer.h"

mglDataContainer::mglDataContainer(DOMElement* configuration)
{

}

void mglDataContainer::init()
{


}

void mglDataContainer::deInit()
{

}

/*
 * Attention - this will add the given pointer to the map - so dont delete it after adding - its not cloned!
 */
void mglDataContainer::addValue(mglValString _key, mglValue* _val)
{
	m_MapValues.insert(std::pair<mglValString,mglValue*>(_key, _val));
}

void mglDataContainer::delValue(mglValString _str)
{
	std::map<mglValString, mglValue*>::iterator valIt = m_MapValues.find(_str);
	delete valIt->second;
	m_MapValues.erase(valIt);
}
