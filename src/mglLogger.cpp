

#include <json.hpp>
#include "mglLogger.h"
#include "mglLogChannel.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;
using json = nlohmann::json;

mglLogger::~mglLogger()
{
}

mglLogger::mglLogger()
{
	m_isInitialized = false;
	for (int i = 0; i < DEF_MAX_LOG_CHANNELS; i++)
		m_Channels[i] = NULL;
}


void mglLogger::configure(json loggerconfig)
{
	int iChannelCount = 0; // Count number of channels - we only allow up to 5 channels
	unsigned short uisReadVal = 0;
	unsigned int ui;
	char* valTagText;

	for (auto& element : loggerconfig["Channels"])
	{
		if (iChannelCount > DEF_MAX_LOG_CHANNELS)
		{
			std::cout << "Warning - Number of log channels exceeds limit of " << iChannelCount << " furhter channels are not regarded.\n";
			continue;
		}
		m_Channels[iChannelCount] = new mglLogChannel(std::string(((element)["stream"]).get<string>()));
		
		// Read channel mask
		auto valTagTextStr = ((element)["mask"]).get<string>();
		valTagText = const_cast<char*>(valTagTextStr.c_str());
		if ((valTagText[0] == '0') && (valTagText[1] == 'x'))
			sscanf(valTagText, "0x%x", &ui);
		else
			sscanf(valTagText, "%u", &ui);
		uisReadVal = (unsigned short)ui;
		m_Channels[iChannelCount]->setMask(uisReadVal);
		
		// Read classes
		if (element.count("classes"))
		{
			valTagTextStr = ((element)["classes"]).get<string>();
			valTagText = const_cast<char*>(valTagTextStr.c_str());
			char* prevPtr = valTagText;
			char* nextPtr = valTagText;

			while (NULL != nextPtr)
			{
				nextPtr = strchr(valTagText, ',');

				if (nextPtr)
					*nextPtr = '\0';

				string newClass = string(prevPtr);
				m_Channels[iChannelCount]->addClassFilter(newClass, 0xffff);
				if (nextPtr)
				{
					nextPtr++;
					prevPtr = nextPtr;
				}
			}
		}				

		// Read libraries
		if (element.count("libraries"))
		{
			valTagTextStr = ((element)["libraries"]).get<string>();
			valTagText = const_cast<char*>(valTagTextStr.c_str());
			char* prevPtr = valTagText;
			char* nextPtr = valTagText;

			while (NULL != nextPtr)
			{
				nextPtr = strchr(valTagText, ',');
			
				if (nextPtr)
					*nextPtr = '\0';

				string newLib = string(prevPtr);
				m_Channels[iChannelCount]->addLibraryFilter(newLib, 0xFFFF);

				if (nextPtr)
				{
					nextPtr++;
					prevPtr = nextPtr;
				}
			}
		}
		iChannelCount++;
	}
	m_isInitialized = true;
	INIT_LOG("mglLogger", "configure(json loggerconfig)");
	LOG_TRACE("Logging initialized...");
}


void mglLogger::log(unsigned short level, static_log_info* info, stringstream& line)
{
	if (!m_isInitialized)
		return;

	for (int i = 0; i < DEF_MAX_LOG_CHANNELS; i++)
	{
		if (m_Channels[i]) // channel is defined?
		{
			if (level == LOG_MASK_EXCEPTION) // Always log exception messages
			{
				m_Channels[i]->log(line);
			}
			else if(m_Channels[i]->getMask() & level) // log level is in the mask?
			{
				if (m_Channels[i]->getLibraryFilter(info->psz_libname) & level)
					if (m_Channels[i]->getClassFilter(info->psz_classname) & level)
						m_Channels[i]->log(line); // todo class, library and its filters check
			}
		}
	}
}

bool mglLogger::destroy(void)
{
	for (int i = 0; i < DEF_MAX_LOG_CHANNELS; i++)
	{
		if (m_Channels[i])
		{
			delete m_Channels[i];
		}
	}

	return true;
}
