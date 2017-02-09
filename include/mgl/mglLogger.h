/*
 * mglLogger.h
 *
 *  Created on: 11.02.2014
 *      Author: chuhlich
 */


#ifndef H_MGL_LOGGER
#define H_MGL_LOGGER

#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>
#include <vector>
#include <json.hpp>

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

// We define our own severity levels
enum severity_level
{
    l_info,
    l_warning,
    l_error,
    l_debug,
    l_trace,
    l_panic,
    l_exception
};

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<severity_level>)

// just a helper macro used by the macros below - don't use it in your code
#define LOG(severity) BOOST_LOG_SEV(logger::get(),severity)

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;

using namespace std;
using json = nlohmann::json;


// ===== log macros =====
#define LOG_TRACE         LOG(severity_level::l_trace)
#define LOG_DEBUG         LOG(severity_level::l_debug)
#define LOG_INFO          LOG(severity_level::l_info)
#define LOG_WARNING       LOG(severity_level::l_warning)
#define LOG_ERROR         LOG(severity_level::l_error)
#define LOG_EXCEPTION     LOG(severity_level::l_exception)

class mglLogger
{
 public:
  ~mglLogger();

  static mglLogger& Inst()
  {
    static mglLogger _instance;
    return _instance;
  }

  void configure(json loggerconfig);

 protected:
  bool m_isInitialized;

  mglLogger();
  mglLogger& operator=(const mglLogger& tm);
};

#endif
