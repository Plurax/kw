#include <json.hpp>
#include "mglLogger.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include <boost/log/core/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <fstream>
#include <ostream>


namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;



// The operator puts a human-friendly representation of the severity level to the stream
std::ostream& operator<< (std::ostream& strm, severity_level level)
{
    static const char* strings[] =
    {
      "I",
      "W",
      "E",
      "D",
      "T",
      "P",
      "X"
    };

    if (static_cast< std::size_t >(level) < sizeof(strings) / sizeof(*strings))
        strm << strings[level];
    else
        strm << static_cast< int >(level);

    return strm;
}


BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)
//BOOST_LOG_ATTRIBUTE_KEYWORD(class_attr, "Class", logging::trivial::severity_level)


mglLogger::~mglLogger()
{
}

mglLogger::mglLogger()
{
	m_isInitialized = false;
}


BOOST_LOG_GLOBAL_LOGGER_INIT(logger, boost::log::sources::severity_logger_mt< severity_level >)
{
  boost::log::sources::severity_logger_mt< severity_level > lg;
  
  logging::add_common_attributes();
  
  return lg;
}

void mglLogger::configure(json loggerconfig)
{
  // Setup the common formatter for all sinks
  logging::formatter fmt = expr::stream
    << ":" << severity << ":"
    << expr::smessage;

  for (auto& element : loggerconfig["Channels"])
  {
    LOG_TRACE << element.dump();
    //! Create the sinks for the global boost logger
    if (((element["type"])).get<string>() == "console")
    {
      logging::add_console_log(
			       std::cout,
			       keywords::format = (
						   expr::stream << expr::format_date_time<     boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
						   << " [" << expr::attr<     severity_level >("Severity") << "]: "
						   << expr::smessage
						   )
			       );
    }
    else
      if (((element["type"])).get<string>() == "file")
      {
	//! We dont use autoflush for files here as we should use cout if necessary!
	logging::add_file_log
	  (
	   keywords::file_name = ((element["name"])).get<string>(),
	   keywords::rotation_size = 10 * 1024 * 1024,
	   keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
	   keywords::format = "[%TimeStamp%] [%Severity%] : %Message%"
	   );	
      }
      else
	if (((element["type"])).get<string>() == string("file"))
	{
	  
	}
  }
  m_isInitialized = true;
  LOG_TRACE << "Logging initialized...";
}
