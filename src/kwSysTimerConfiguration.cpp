#include "kw/kwSysTimerConfiguration.h"
#include <string.h>

kwSysTimerConfiguration::kwSysTimerConfiguration()
{
  m_iMessageType = 0;
}

kwSysTimerConfiguration::kwSysTimerConfiguration(json config)
{
  auto msgID_str = std::make_shared<string>(((config["MessageId"])).get<string>());
  m_iMessageType = atoi(msgID_str->c_str());;

  Payload = config["Payload"];
}


kwSysTimerConfiguration::~kwSysTimerConfiguration()
{
}

json kwSysTimerConfiguration::getPayload()
{
  return Payload;
}

int kwSysTimerConfiguration::getMessageType()
{
  return m_iMessageType;
}
