/*
 * kwMessage.h
 *
 *  Created on: 09.11.2013
 *      Author: chuhlich
 */

#ifndef KWMESSAGE_H_
#define KWMESSAGE_H_

#include "kw/kwValString.h"
#include "kw/kwObject.h"

enum eMessageType
{
	mtInput = 0
};

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class kwMessage : public kwObject
{
public:
	kwMessage(int messagetype);
	virtual ~kwMessage();

	int getMessageType();

	void setMessageText(kwValString& message);
	void setMessageText(const char* message);

	kwValString* getMessageText();
  json getJsonObj();

protected:
	int m_iMessageType;
	kwValString* m_MessageText;
  json json_obj;
};

#endif /* KWMESSAGE_H_ */
