/*
 * kwSysTimerConfiguration.h
 *
 *  Created on: 11.07.2018
 *      Author: chuhlich
 */

#ifndef KWSYSTIMERCONFIGURATION_H_
#define KWSYSTIMERCONFIGURATION_H_

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class kwSysTimerConfiguration
{
 public:
  kwSysTimerConfiguration();
  kwSysTimerConfiguration(json config);
  ~kwSysTimerConfiguration();

  json getPayload();
  int getMessageType();
 private:
	int m_iMessageType;
  json Payload;
};

#endif /* KWSYSTIMERCONFIGURATION_H_ */
