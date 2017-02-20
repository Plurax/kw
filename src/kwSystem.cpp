
#include <vector>


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <exception>
//#include <stdexcept>
#include "kwReleaseInfo.h"
#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <iostream>
#include "boost/filesystem.hpp"

#ifdef WIN32
#include "Windows.h"
#include <typeinfo>
#else
#include <cxxabi.h>
#endif

#include "kwSystem.h"
#include "kwTechnicalException.h"
#include "kwValCoord.h"


using namespace std;

kwSystem::kwSystem()
{
}

/**
 * Main initialization routine.
 *
 */
void kwSystem::init(kwValString& configfile)
{
  /* Note this is not used as shared pointer as we use this inforation within lib handles which 
     are propably initialized with external shared lib factories!
  */
  m_libInfo = new kwLibraryInfo("kw", "0.2", "Embedded GL Toolkit", "Christoph Romas",	"MIT - www.electroknit.io");

  kwLibraryManager& dsManager = kwLibraryManager::Inst();
  dsManager.init();

  readConfiguration(configfile);
}

/**
 * Destructor
 */
kwSystem::~kwSystem()
{
}


/**
 * Reads the complete configuration file and creates the corresponding graphic objects via
 * loading of shared libs and factory pattern.
 * @param configFile - string containing a full path file for the configuration
 */
void kwSystem::readConfiguration(kwValString& configFile)
{
  errno = 0;
  if (!boost::filesystem::exists(configFile.str()->c_str()))
  {
    if( errno == ENOENT )      // errno declared by include file errno.h
      throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
    else if( errno == ENOTDIR )
      throw ( std::runtime_error("A component of the path is not a directory."));
    else if( errno == ELOOP )
      throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
    else if( errno == EACCES )
      throw ( std::runtime_error("Permission denied."));
    else if( errno == ENAMETOOLONG )
      throw ( std::runtime_error("File can not be read\n"));
  }

  std::stringstream ss;
  boost::filesystem::path p(configFile.str()->c_str());
  ss << std::ifstream( p.string().c_str() ).rdbuf();

  json config(ss);

  try
  {
    kwLogger::Inst().configure(config["Logging"]);
    //		m_Configuration.init(config["AppConfiguration"]);
    createDataLayer(config["DataLayer"]);
    //		m_FontProvider->loadFonts(config["Font"]);
    setMessageHandlers(config["MessageHandlers"]);
    //		m_TextureManager->initTextures(config["Textures"]);
  }
  catch (kwTechnicalException& e)
  {
    LOG_EXCEPTION << e.getMessage();
  }
  catch (exception& e)
  {
    LOG_EXCEPTION << "Exception occured during init!: " << e.what();
  }
}


/**
 * This will configure the message handlers to be assigned on the different message IDs.
 * This is completely flexible to provide own handlers. The only handler which is intern
 * is the GUI Message for inputs with ID 0.
 *
 * @param _currentElement
 */
void kwSystem::setMessageHandlers(json messageconfig)
{
  int messageId = -1; // -1 is initial faulty - 0 is forbidden (internal gui messages)
  shared_ptr<kwValString> handlerlibname = nullptr;
  shared_ptr<kwValString> handlerclassname = nullptr;
  shared_ptr<string> msgID_str = nullptr;

  if (messageconfig == nullptr)
  {
    LOG_INFO << "No message handlers found in config...";
    return;
  }
  else
    LOG_TRACE << "Initializing message handlers...";

  auto sMainclassname = make_shared<kwValString>("kwMessageHandler");

  for (auto& element : messageconfig)
  {
    handlerlibname = make_shared<kwValString>(((element["handlerLib"])).get<string>());
    handlerclassname = make_shared<kwValString>(((element["handlerClass"])).get<string>());
    msgID_str = make_shared<string>(((element["MessageId"])).get<string>());
    messageId = atoi(msgID_str->c_str());;

    /* Now create the message handler from the lib and attach it onto the ID
     */
    if (handlerlibname != nullptr && handlerclassname != nullptr && msgID_str != nullptr)
    {
      // After we created the object we can attach the handler if it exists
      LOG_TRACE << "Got a configured handler library: " << *handlerlibname << " class: " << *handlerclassname << " MessageID: " << messageId;
      shared_ptr<kwObject> funct = kwLibraryManager::Inst().createObject(handlerlibname, handlerclassname, sMainclassname, element["config"]);
      auto addObj = static_pointer_cast<kwMessageHandler>(funct);
      m_mMessageHandlers.insert(std::pair<int, shared_ptr<kwMessageHandler>>(messageId, addObj));
      handlerlibname.reset();
      handlerclassname.reset();
      msgID_str.reset();
    }
  }
}

/**
 * Creates the datalayer configured below the given element.
 * After creation of the object each one is initialized.
 * @param _currentElement
 */
void kwSystem::createDataLayer(json _currentElement)
{
  shared_ptr<kwDataSource> thisDS;

  LOG_TRACE << "Loading and initializing data sources...";

  for (json::iterator it = _currentElement.begin(); it != _currentElement.end(); ++it) 
  {
    if ( it.key() == "DataSource")
    {
      /* The JSON should always contain the following tags at this point:
       * <name>,<libname>, <classname> and <conf>
       */

      auto name = make_shared<kwValString>(((*it)["name"]).get<string>());
      auto libname = make_shared<kwValString>(((*it)["libname"]).get<string>());
      auto classname = make_shared<kwValString>(((*it)["classname"]).get<string>());
      auto sMainclassname = make_shared<kwValString>("kwDataSource");

      auto configuration = (*it)["configuration"];

      // Create the configured element via the factory

      auto obj = kwLibraryManager::Inst().createObject(libname,
							classname,
							sMainclassname,
							configuration);

      thisDS = static_pointer_cast<kwDataSource>(obj);
      if (thisDS)
	m_DataSources.insert(pair<kwValString, shared_ptr<kwDataSource>>(*name,thisDS));

      thisDS = nullptr; // Kill local reference
    }
  }

  map<kwValString, shared_ptr<kwDataSource>>::iterator itDS;
  for (itDS = m_DataSources.begin(); itDS != m_DataSources.end(); itDS++)
    itDS->second->init();
  LOG_TRACE << "Data sources completed...";
}


/**
 * Retrieve a datasource with the given name.
 * Application code should know the type as the retrieved object is a general kwDataSource pointer.
 * @param _name
 * @return
 */
shared_ptr<kwDataSource> kwSystem::getDataSource(kwValString _name)
{
  kwDataSourceMap::iterator itDS = m_DataSources.find(_name);
  if (itDS == m_DataSources.end())
    return nullptr;
  else
    return itDS->second;
}


/**
 * This function will process all events. This is used to allow separate message handlings,
 * for example for socket command reception etc.
 *
 */
void kwSystem::processMessages()
{
  while (!m_MessageQueue.empty())
  {
    shared_ptr<kwMessage> processing = m_MessageQueue.front();
    /* Search for associated Input type within the message handler map
     * and execute it. Otherwise we log an ERR and delete the message.
     */
    kwMessageHandlerMap::iterator findIt = m_mMessageHandlers.find(processing->getMessageType());
    if (findIt != m_mMessageHandlers.end())
    {
      // This will execute the handler
      (*findIt->second)(processing);
    }
    else
    {
      LOG_TRACE << "Could not find handler for message type!";
    }
    m_MessageQueue.pop();
  }
}


/**
 * Add a message onto the Queue. This can be every Message we like to process...
 *
 * @param mess The message to add.
 */
void kwSystem::addMessage(shared_ptr<kwMessage> mess)
{
  m_MessageQueue.push(mess);
}


void kwSystem::destroy()
{
  LOG_TRACE << "Clearing data sources...";
  map<kwValString, shared_ptr<kwDataSource>>::iterator itDS;
  for (itDS = m_DataSources.begin(); itDS != m_DataSources.end(); itDS++)
    itDS->second->deInit();
}


