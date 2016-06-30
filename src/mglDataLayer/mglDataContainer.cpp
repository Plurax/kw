/*
 * mglDataContainer.cpp
 *
 *  Created on: 25.04.2014
 *      Author: cromas
 */


#include "mglDataLayer/mglDataContainer.h"

mglDataContainer::mglDataContainer(json configuration)
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
void mglDataContainer::addValue(mglValString _key, shared_ptr<mglValue> _val)
{
	m_MapValues.insert(std::pair<mglValString, shared_ptr<mglValue>>(_key, _val));
}

void mglDataContainer::delValue(mglValString _str)
{
	std::map<mglValString, shared_ptr<mglValue>>::iterator valIt = m_MapValues.find(_str);
	m_MapValues.erase(valIt);
}


shared_ptr<mglValue> mglDataContainer::getValue(mglValString key)
{
	std::map<mglValString, shared_ptr<mglValue>>::iterator valIt = m_MapValues.find(key);
	return valIt->second;
}
