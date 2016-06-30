/*
 * mglAppConfiguration.cpp
 *
 *  Created on: 19.01.2014
 *      Author: cromas
 */

#include "mglAppConfiguration.h"
#include "mglDebug/mglLogger.h"

void mglAppConfiguration::init(json appconfig)
{
	INIT_LOG("mglAppConfiguration", "init(json appconfig)");

	unsigned long int uisReadVal = 0;
	char* valTagText;

	// Set defaults for delaystart and end
	m_contextDelayStart = boost::posix_time::duration_from_string(std::string("00:00:00.100"));;
	m_contextDelayEnd = boost::posix_time::duration_from_string(std::string("00:00:00.100"));

	auto numberval = (((appconfig)["GL"]["xres"]).get<int>());
	m_xres = (unsigned short)numberval;

	numberval = (((appconfig)["GL"]["yres"]).get<int>());
	m_yres = (unsigned short)numberval;

	m_ContextAnimationClass = make_shared<mglValString>(((appconfig)["GL"]["ContextAnimationClass"]).get<string>());

	m_ContextAnimationLib = make_shared<mglValString>(((appconfig)["GL"]["ContextAnimationLib"]).get<string>());

	valTagText = const_cast<char*>(((appconfig)["GL"]["ContextDelayStart"]).get<string>().c_str());
							
	m_contextDelayStart = boost::posix_time::duration_from_string(valTagText);;
	LOG_DEBUG("DelayStart: " << m_contextDelayStart);

	valTagText = const_cast<char*>(((appconfig)["GL"]["ContextDelayEnd"]).get<string>().c_str());

	m_contextDelayEnd = boost::posix_time::duration_from_string(valTagText);;

	numberval = (((appconfig)["GL"]["FullScreen"]).get<bool>());
	if (numberval > 0)
		m_FullScreen = true;
	else
		m_FullScreen = false;

	LOG_DEBUG("yres: " << m_yres << " xres: " << m_xres);
}

unsigned short mglAppConfiguration::getYRes()
{
	return m_yres;
}

unsigned short mglAppConfiguration::getXRes()
{
	return m_xres;
}


bool mglAppConfiguration::getFullScreen()
{
	return m_FullScreen;
}

shared_ptr<mglValString> mglAppConfiguration::getContextAnimationClass()
{
	return m_ContextAnimationClass;
}

shared_ptr<mglValString> mglAppConfiguration::getContextAnimationLib()
{
	return m_ContextAnimationLib;
}

boost::posix_time::time_duration mglAppConfiguration::getContextAnimationDelayStart()
{
	return m_contextDelayStart;
}

boost::posix_time::time_duration mglAppConfiguration::getContextAnimationDelayEnd()
{
	return m_contextDelayEnd;
}


