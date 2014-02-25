

#ifndef H_MGL_LOGGER
#define H_MGL_LOGGER

#include "mglLogChannel.h"
#include "mglLogDevice.h"
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

class mglDynamicLoggerInfo;
using namespace std;

struct __static_log_info {
	const char* psz_libname;
	const char* psz_file;
	const char* psz_classname;
	const char* psz_method;
};

typedef struct __static_log_info static_log_info;

#define INIT_LOG(classname, methodname) \
	static __static_log_info _stat_log_info = {__LIBNAME, __FILE__, classname, methodname}

#define LOG_LEVEL(level,tag,text) \
	do { \
		std::stringstream line; \
		line <<  _stat_log_info.psz_libname << ";" << std::setw(15) << _stat_log_info.psz_file << ";" << std::setw(0) << _stat_log_info.psz_method << ";" << __LINE__  << ";" << tag << ": " << text; \
		mglLogger::Inst().log(level,&_stat_log_info,line); \
	} \
	while (false);

#define LOG_MASK_EXCEPTION (unsigned short)0x0040
#define LOG_MASK_PANIC (unsigned short)0x0020
#define LOG_MASK_TRACE (unsigned short)0x0010
#define LOG_MASK_DEBUG (unsigned short)0x0008
#define LOG_MASK_ERROR (unsigned short)0x0004
#define LOG_MASK_WARN  (unsigned short)0x0002
#define LOG_MASK_INFO  (unsigned short)0x0001


#define LOG_INFO(text) LOG_LEVEL(LOG_MASK_INFO,"I",text)
#define LOG_WARN(text) LOG_LEVEL(LOG_MASK_WARN,"W",text)
#define LOG_ERROR(text) LOG_LEVEL(LOG_MASK_ERROR,"E",text)
#define LOG_DEBUG(text) LOG_LEVEL(LOG_MASK_DEBUG,"D",text)
#define LOG_TRACE(text) LOG_LEVEL(LOG_MASK_TRACE,"T",text)
#define LOG_PANIC(text) LOG_LEVEL(LOG_MASK_PANIC,"P",text)

#define LOG_EXCEPTION(text) LOG_LEVEL(LOG_MASK_EXCEPTION,"X",text)
/*\
		do { \
			std::stringstream line; \
			line <<  _stat_log_info.psz_libname << ";" << _stat_log_info.psz_file << ";"; \
			line << _stat_log_info.psz_method << ";" << __LINE__  << ";" << tag << ": "; \
			line << "######## EXCEPTION Exception exception ########\n## ERRNO: " << errno << "\n" << "## Message: " << text; \
			mglLogger::Inst().log(level,&_stat_log_info,line); \
		} \
		while (false);
*/

#define DEF_MAX_LOG_CHANNELS 5

class mglLogger
{
public:
	~mglLogger();

	static mglLogger& Inst()
		{
			static mglLogger _instance;
			return _instance;
		}

	void configure(xercesc::DOMNode* loggerconfig);

	void addLibraryFilter(string& channel, string& name, unsigned short value);
	void addClassFilter(string& channel, string& name, unsigned short value);

	void log(unsigned short level, static_log_info* info, stringstream& line);
	bool destroy(void);
protected:
	mglLogChannel* m_Channels[DEF_MAX_LOG_CHANNELS];

	bool m_isInitialized;

	mglLogger();
	mglLogger& operator=(const mglLogger& tm);
};

#endif
