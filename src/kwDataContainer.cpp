/*
 * kwDataContainer.cpp
 *
 *  Created on: 25.04.2014
 *      Author: chuhlich
 */


#include "kwDataContainer.h"
#include "kwValInteger.h"
#include "kwValBool.h"
#include "kwValUnsignedInteger.h"
#include "kwValFloat.h"
#include "kwValJsonObject.h"


kwDataContainer::kwDataContainer(json configuration)
{
  for (json::iterator it = configuration.begin(); it != configuration.end(); ++it) 
  {
      // Avoid null as we cant do something with null value - instead
      // the requested key will return value not found.
      // if (it->type() == json::value_t::null)
      //     addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValue>(nullptr));
      if (it->type() == json::value_t::boolean)
          addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValBool>(it->get<bool>()));
      if (it->is_number_integer())
      {
          addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValInteger>(it->get<int>()));
      }
      if (it->type() == json::value_t::number_unsigned)
          addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValUnsignedInteger>(it->get<uint>()));
      if (it->type() == json::value_t::number_float)
          addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValFloat>(it->get<float>()));
      if (it->is_string())
      {
          addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValString>(it->get<string>()));
      }
      if (it->type() == json::value_t::object)
          addValue(std::make_shared<kwValString>(it.key()), std::make_shared<kwValJsonObject>(it.value()));
  }
}

void kwDataContainer::init()
{
}

void kwDataContainer::deInit()
{

}

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
