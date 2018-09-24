/*
 * kwDataContainer.cpp
 *
 *  Created on: 25.04.2014
 *      Author: chuhlich
 */


#include "kwDataContainer.h"

kwDataContainer::kwDataContainer(json configuration)
{
  for (json::iterator it = configuration.begin(); it != configuration.end(); ++it) 
  {
      addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValString>(it->get<string>()));
  }
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
void kwDataContainer::addValue(kwValString _key, shared_ptr<kwValue<kwValString>> _val)
{
	m_MapValues.insert(std::pair<kwValString, shared_ptr<kwValue<kwValString>>>(_key, _val));
}

void kwDataContainer::delValue(kwValString _str)
{
	std::map<kwValString, shared_ptr<kwValue<kwValString>>>::iterator valIt = m_MapValues.find(_str);
	m_MapValues.erase(valIt);
}


shared_ptr<kwValue<kwValString>> kwDataContainer::getValue(kwValString key)
{
	std::map<kwValString, shared_ptr<kwValue<kwValString>>>::iterator valIt = m_MapValues.find(key);
    if (valIt != m_MapValues.end())
        return valIt->second;
    else
        return std::make_shared<kwValString>("Value not found");
}
