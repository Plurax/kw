/*
 * kwDataContainer.cpp
 *
 *  Created on: 25.04.2014
 *      Author: chuhlich
 */


#include "kwDataContainer.h"

kwDataContainer::kwDataContainer(json configuration)
{

}

void kwDataContainer::init()
{


}

void kwDataContainer::deInit()
{

}

/*
 * Attention - this will add the given pointer to the map - so dont delete it after adding - its not cloned!
 */
void kwDataContainer::addValue(kwValString _key, shared_ptr<kwValue> _val)
{
	m_MapValues.insert(std::pair<kwValString, shared_ptr<kwValue>>(_key, _val));
}

void kwDataContainer::delValue(kwValString _str)
{
	std::map<kwValString, shared_ptr<kwValue>>::iterator valIt = m_MapValues.find(_str);
	m_MapValues.erase(valIt);
}


shared_ptr<kwValue> kwDataContainer::getValue(kwValString key)
{
	std::map<kwValString, shared_ptr<kwValue>>::iterator valIt = m_MapValues.find(key);
	return valIt->second;
}
