
#include <vector>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdexcept>
#include "mglReleaseInfo.h"

#include "mglSystem.h"

using namespace xercesc;
using namespace std;

mglSystem::mglSystem()
{
}

/**
 * Main initialization routine.
 *
 * @param context - opengl context
 * @param ptr - flushGL function pointer which is called by Draw after rendering.
 */
void mglSystem::init(GLXContext context, void (*ptr)(void))
{
	m_libInfo = new mglLibraryInfo("mgl", "0.1", "Embedded GL Toolkit", "Christoph Romas",	"Proprietary - tbd");
	// Insert default factory into the list
	mglGuiLibManager& objManager = mglGuiLibManager::Inst();
	objManager.init();
	mglDataSourceManager& dsManager = mglDataSourceManager::Inst();
	dsManager.init();

	flushGL = ptr;
	/* Prepare XML Parser */
   try
   {
	   XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
   }
   catch( XMLException& e )
   {
      char* message = XMLString::transcode( e.getMessage() );
      cerr << "XML toolkit initialization error: " << message << endl;
      XMLString::release( &message );
      // throw exception here to return ERROR_XERCES_INIT
   }

   // Tags and attributes used in XML file.
   // Can't call transcode till after Xerces Initialize()
   m_ConfigFileParser = new XercesDOMParser;

   m_FontProvider = new mglFontProvider();
   m_TextureManager = new mglTextureManager();

   mglValString configfile("Configuration.xml");
	readConfiguration(configfile);

	m_CurrentMainFrame = NULL;
	m_CurrentMenu = NULL;

	m_lastActionCausedByTouch = false;
	m_vSelectionContexts.push_back(new mglSelectionContext());
}

mglSystem::~mglSystem()
{
	uint uiIndex;
	for (uiIndex = 0; uiIndex < m_lMainFrames.size(); uiIndex++)
		delete m_lMainFrames.at(uiIndex); // delete the root frame objects
	m_lMainFrames.clear(); // clear all registered root frames
}


/**
 * Processes an input message.
 * @param Message
 * @return
 */
mglMessage* mglSystem::processInputMessage(mglInputMessage* Message)
{
	INIT_LOG("mglSystem", "processInputMessage(mglInputMessage* Message)");
	// find the target object
	if ((Message->getInputType() != eInputIGR) &&
			(Message->getButton() != BTN_IGR))
	{
		mglGuiObject *Target = getTargetWindow(Message->getCoord());
		if (Target != NULL)
			if (Target->getGuiAction() != NULL)
			{
				Message->setTarget(Target);

				return Target->ProcessMessage(Message);
			}
	}
	else
	{
		if (Message->getButton() == BTN_IGR)
		{
			// Remap to button 1?
			if (m_vSelectionContexts.back()->m_Focus != NULL)
			{
				LOG_TRACE("Entering focus handler");
				if (!m_vSelectionContexts.back()->m_Focus->getOptionMask() & OBJ_EDITABLE)
				{
					LOG_TRACE("Object is not editable");
					Message->setTarget(m_vSelectionContexts.back()->m_Focus);
					m_vSelectionContexts.back()->m_Focus->ProcessMessage(Message);
				}
			}
			// May be functor logic maps the input onto the mt1 behaviour - so we change the state to focussed again here...
			if (Message->getInputType() == eInputMouseButtonRelease)
			{
				if (m_vSelectionContexts.back()->m_Focus != NULL)
					if (m_vSelectionContexts.back()->m_Editing == NULL)
						m_vSelectionContexts.back()->m_Focus->setState(OBJ_STATE_FOCUSSED);

				LOG_TRACE("Object is editable");
				if (m_vSelectionContexts.back()->m_Editing == NULL)
				{
					m_vSelectionContexts.back()->m_Editing = m_vSelectionContexts.back()->m_Focus;
					m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_SELECTED);
				}
				else
				{
					m_vSelectionContexts.back()->m_Editing = NULL;
					m_vSelectionContexts.back()->m_Focus->setState(OBJ_STATE_FOCUSSED);
				}
			}
		}
		else
		{
			// we are in focus level - step through the selection list
			if (m_vSelectionContexts.back()->m_Editing == NULL)
			{
				mglGuiObject* pTemp = NULL;
				mglGuiObject* pSwap = NULL;

				int iCount = Message->getIGRCount();
				bool bForward,bEntry = false;

				if (iCount > 0)
					bForward = true;
				else
				{
					bForward = false;
					iCount *= -1;
				}

				if (m_vSelectionContexts.back()->m_pCurrentSelectionList == NULL)
				{
					bEntry = true;
					m_vSelectionContexts.back()->m_pCurrentSelectionList = m_vSelectionContexts.back()->m_SelectListParent->getChildren();
					if (bForward)
						pTemp = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->begin());
					else
						pTemp = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->rbegin());
				}
				else
				{
					pTemp = m_vSelectionContexts.back()->m_Focus;
					m_vSelectionContexts.back()->m_Focus->setState(OBJ_STATE_STANDARD);
				}

				while ((iCount != 0) && (pTemp != NULL))
				{
					if (!bEntry)
					{
						if (bForward)
							pSwap = pTemp->next();
						else
							pSwap = pTemp->prev();

						if (pSwap == NULL) // reached end of concatenation
						{
							if (bForward)
								pSwap = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->begin());
							else
								pSwap = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->rbegin());
						}

						pTemp = pSwap;
					}
					if (pTemp)
						if (pTemp->getOptionMask() & OBJ_SELECTABLE)
							iCount--;
				}

				if (pTemp != NULL)
				{
					pTemp->setState(OBJ_STATE_FOCUSSED);
					m_vSelectionContexts.back()->m_Focus = pTemp;
				}
				else
				{
					m_vSelectionContexts.back()->m_Focus = NULL;
					m_vSelectionContexts.back()->m_pCurrentSelectionList = NULL;
				}
			}
			else
			{
				int iCount = Message->getIGRCount();
				mglGuiObjectEditable* objEditable = static_cast<mglGuiObjectEditable*>(m_vSelectionContexts.back()->m_Editing);
				// An editable has to implement the additional editable class functions to provide modification via system layer
				objEditable->applyIGRCount(iCount);
			}
		}
	}
	return NULL;
}


/**
 * Render the current shown content (Mainframe and possibly active menu).
 */
void mglSystem::Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // render all the currently active main frame
	m_CurrentMainFrame->Draw();

	glLoadIdentity();
	glTranslatef(0.0, 0.0, 1.0); // Menu layer is translated one unit onto the user (we are in projection - this will not cause zoom)

	if (m_CurrentMenu != NULL)
		m_CurrentMenu->Draw();

	(*flushGL)();

}

/**
 * Determine the gui object which is at the given coordinates.
 * This function regards mainframes and menus. Only visible marked objects are regarded.
 * @param pt
 * @return
 */
mglGuiObject* mglSystem::getTargetWindow(mglValCoord pt)
{
	mglGuiObject* destination;

	destination = m_CurrentMenu; // set target to current menu if not null

	if (destination != NULL)
	{
		if (!destination->isVisible())
			return 0;

		// then search within the concatenation for the final input target
		if ((pt.getX() >= (m_CurrentMenu)->GetX()) &&
			(pt.getX() < ((m_CurrentMenu)->GetX() + (m_CurrentMenu)->GetWidth())) &&
			(pt.getY() <= (m_CurrentMenu)->GetY()) &&
			(pt.getY() > ((m_CurrentMenu)->GetY() - (m_CurrentMenu)->GetHeight())))
		{
			destination = m_CurrentMenu->getChildAtPosition(pt);
			return destination;
		}
	}

	destination = m_CurrentMainFrame; // set target to current root mainframe
	if (!destination->isVisible())
		return 0;

	// then search within the concatenation for the final input target
	if ((pt.getX() >= (m_CurrentMainFrame)->GetX()) &&
		(pt.getX() < ((m_CurrentMainFrame)->GetX() + (m_CurrentMainFrame)->GetWidth())) &&
		(pt.getY() <= (m_CurrentMainFrame)->GetY()) &&
		(pt.getY() > ((m_CurrentMainFrame)->GetY() - (m_CurrentMainFrame)->GetHeight())))
	{
		destination = m_CurrentMainFrame->getChildAtPosition(pt);
		return destination;
	}
	return 0;
}

mglGuiObject* mglSystem::getMainFrameByID(unsigned int ID)
{
	if (ID < m_lMainFrames.size())
		return m_lMainFrames.at(ID);
	else
		return 0;
}

mglGuiObject* mglSystem::getMenuByID(unsigned int ID)
{
	if (ID < m_lMenus.size())
		return m_lMenus.at(ID);
	else
		return 0;
}

/**
 * Sets the mainframe to be shown.
 * This also will change the first selection context object to the newly set frame!
 * This behaviour allows changing main frames out of menus.
 * @param MainFrame
 */
void mglSystem::SetMainFrame(mglGuiObject *MainFrame)
{
	m_CurrentMainFrame = MainFrame;
	m_vSelectionContexts.front()->m_pCurrentSelectionList = NULL;

	m_vSelectionContexts.front()->m_SelectListParent = m_CurrentMainFrame;
}

void mglSystem::openMenu(mglGuiObject *Menu)
{
	m_vSelectionContexts.push_back(new mglSelectionContext());

	m_CurrentMenu = Menu;
	m_vSelectionContexts.back()->m_SelectListParent = m_CurrentMenu;
	mglGuiObject* obj = NULL;

	if (!m_lastActionCausedByTouch)
	{
		m_vSelectionContexts.back()->m_pCurrentSelectionList = m_CurrentMenu->getChildren();
		mglGuiObjectList::iterator it = m_vSelectionContexts.back()->m_pCurrentSelectionList->begin();
		while (it != m_vSelectionContexts.back()->m_pCurrentSelectionList->end())
		{
			obj = *it;
			if (obj->getOptionMask() & OBJ_SELECTABLE)
				break;
		}
		m_vSelectionContexts.back()->m_Focus = obj;
	}
	else
		m_vSelectionContexts.back()->m_pCurrentSelectionList = NULL;

	m_vSelectionContexts.back()->m_SelectListParent = m_CurrentMenu;
	m_vSelectionContexts.back()->m_Menu = m_CurrentMenu;
}

/**
 * This will close the menu.
 * If there were other menus opened before, all their selections will be thrown away and we go directly to mainframe!
 */
void mglSystem::closeMenu()
{
	while (m_vSelectionContexts.size() > 1)
	{
		delete m_vSelectionContexts.back();
		m_vSelectionContexts.pop_back();
	}
	m_CurrentMenu = NULL;
}


/**
 * This will return from the currently opened menu to the previous one.
 * If there was no menu opened before this one, same is done as in close...
 */
void mglSystem::returnFromMenu()
{
	delete m_vSelectionContexts.back();
	m_vSelectionContexts.pop_back();
	m_CurrentMenu = m_vSelectionContexts.back()->m_Menu;
}


/**
 * Reads the complete configuration file and creates the corresponding graphic objects via
 * loading of shared libs and factory pattern.
 * @param configFile - string containing a full path file for the configuration
 */
void mglSystem::readConfiguration(mglValString& configFile)
{
	INIT_LOG("mglSystem", "readConfiguration(mglValString& configFile)");

	// Test to see if the file is ok.
   struct stat fileStatus;

   errno = 0;
   if(stat(configFile.str()->c_str(), &fileStatus) == -1) // ==0 ok; ==-1 error
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

   m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );
   m_ConfigFileParser->setDoNamespaces( false );
   m_ConfigFileParser->setDoSchema( false );
   m_ConfigFileParser->setLoadExternalDTD( false );

   XMLCh* TAG_GUI = XMLString::transcode("GUI");
   XMLCh* TAG_DataLayer= XMLString::transcode("DataLayer");
   XMLCh* TAG_Menus = XMLString::transcode("MENUS");
   XMLCh* TAG_AppConfiguration = XMLString::transcode("AppConfiguration");
   XMLCh* TAG_Logging = XMLString::transcode("Logging");
   XMLCh* TAG_Fonts= XMLString::transcode("Fonts");
   XMLCh* TAG_Textures = XMLString::transcode("Textures");

   try
   {
      m_ConfigFileParser->parse( configFile.str()->c_str() );

      // no need to free this pointer - owned by the parent parser object
      DOMDocument* xmlDoc = m_ConfigFileParser->getDocument();

      // Get the top-level element: NAme is "root". No attributes for "root"

      DOMElement* elementRoot = xmlDoc->getDocumentElement();
      if( !elementRoot )
    	  throw(std::runtime_error( "empty XML document" ));
	  // Parse XML file for tags of interest: "ApplicationSettings"
      // Look one level nested within "root". (child of root)

		DOMNodeList*      children = elementRoot->getChildNodes();
		const  XMLSize_t nodeCount = children->getLength();

		// For all nodes, children of "root" in the XML tree.

		for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
		{
			DOMNode* currentNode = children->item(xx);
			if( currentNode->getNodeType() &&  // true is not NULL
					currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
			{
				// Found node which is an Element. Re-cast node as element
				DOMElement* currentElement
							= dynamic_cast< xercesc::DOMElement* >( currentNode );

				if ( XMLString::equals(currentElement->getTagName(), TAG_Logging))
				{
					mglLogger::Inst().configure(currentNode);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_AppConfiguration))
				{
					m_Configuration.init(currentNode);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_DataLayer))
				{
					createDataLayer(currentNode);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_GUI))
				{
					createGUIfromXML(currentNode, NULL, NULL, m_lMainFrames);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_Menus))
				{
					createGUIfromXML(currentNode, NULL, NULL, m_lMenus);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_Fonts))
				{
					m_FontProvider->loadFonts(currentNode);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_Textures))
				{
//					if (true == m_TextureManager->LoadTexture("/home/cromas/Downloads/testbutton.png", GL_RGBA, GL_RGB, 0, 0))
//						LOG_TRACE("png Texture loaded");
				}
			}
	  }
   }
   catch( xercesc::XMLException& e )
   {
      char* message = xercesc::XMLString::transcode( e.getMessage() );
      ostringstream errBuf;
      errBuf << "Error parsing file: " << message << flush;
      XMLString::release( &message );

      XMLString::release(&TAG_GUI);
      XMLString::release(&TAG_DataLayer);
      XMLString::release(&TAG_Menus);
      XMLString::release(&TAG_AppConfiguration);
      XMLString::release(&TAG_Logging);
      XMLString::release(&TAG_Textures);
   }

   XMLString::release(&TAG_GUI);
   XMLString::release(&TAG_DataLayer);
   XMLString::release(&TAG_Menus);
   XMLString::release(&TAG_AppConfiguration);
   XMLString::release(&TAG_Logging);
   XMLString::release(&TAG_Textures);
}

/**
 *
 * @param GUIELement - GUI Tag (root element for gui definition)
 * @param parent - parent element for recursive usage
 * @param prev - previous element for recursive usage
 * @param listToAdd - pointer to the list where root objects will be added (menus or frames)
 */
void mglSystem::createGUIfromXML(DOMNode* GUIELement, mglGuiObject* parent, mglGuiObject* prev, mglGuiObjectList& listToAdd)
{
	INIT_LOG("mglSystem", "createGUIfromXML(DOMNode* GUIELement, mglGuiObject* parent, mglGuiObject* prev)");

	DOMNodeList*      children = GUIELement->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	mglGuiObject* thisWindow = NULL;
	mglGuiObject* prevWindow = NULL;

	XMLCh* TAG_mglWindowItem = XMLString::transcode("mglWindowItem");

	// For all nodes, children of "GUI" in the XML tree.
	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
			if ( XMLString::equals(currentElement->getTagName(), TAG_mglWindowItem))
			{
				/* The XML should always contain the following tags at this point:
				 * <name>,<libname>, <classname>, <handlerLib>, <handlerClass> and <configuration>
				 * The programmer can even replace the frame object implementation by using
				 * his own library at this point!
				 */

				DOMElement* DE_name = currentElement->getFirstElementChild();
				DOMElement* DE_libname = DE_name->getNextElementSibling();
				DOMElement* DE_classname = DE_libname->getNextElementSibling();

				DOMElement* DE_func_libname = DE_classname->getNextElementSibling();
				DOMElement* DE_func_classname = DE_func_libname->getNextElementSibling();

				DOMElement* DE_configuration = DE_func_classname->getNextElementSibling();
				DOMElement* DE_children = DE_configuration->getNextElementSibling();

				/*
				 * Name is mandatory
				 */
				LOG_TRACE("Got GUI Element named: " << XMLString::transcode(DE_name->getTextContent()));

				// Create the configured element via the factory

				mglValString* name = new mglValString(XMLString::transcode(DE_name->getTextContent()));
				mglValString* libname = new mglValString(XMLString::transcode(DE_libname->getTextContent()));
				mglValString* classname = new mglValString(XMLString::transcode(DE_classname->getTextContent()));

				thisWindow = mglGuiLibManager::Inst().createGUIObject(libname,
													classname,
													DE_configuration);

				libname = new mglValString(XMLString::transcode(DE_func_libname->getTextContent()));
				classname = new mglValString(XMLString::transcode(DE_func_classname->getTextContent()));

				// After we created the object we can attach the handler if it exists
				mglGuiActionFunctor* funct = mglGuiLibManager::Inst().createGuiAction(libname, classname);
				thisWindow->Connect(funct);

				// A created gui object is also registered by its name
				m_mGuiObjects.insert(std::pair<mglValString,mglGuiObject*>(mglValString(*name),thisWindow));

				// We are at parent level - so this is a main frame
				if (parent == NULL)
					listToAdd.push_back(thisWindow);
				else
				{
					thisWindow->setParentWindow(parent);
					parent->AddChild(thisWindow);
				}

				thisWindow->setPrevWindow(prevWindow);
				thisWindow->setNextWindow(NULL);
				if (prevWindow)
					prevWindow->setNextWindow(thisWindow);

				// Now ascend down and create the children
				if (DE_children->getChildNodes()->getLength() > 0)
				{
					createGUIfromXML(DE_children, thisWindow, NULL, listToAdd);
				}
				prevWindow = thisWindow;
			}
		}
	}
	XMLString::release(&TAG_mglWindowItem);
}

/**
 * Creates the datalayer configured below the given element.
 * After creation of the object each one is initialized.
 * @param _currentElement
 */
void mglSystem::createDataLayer(DOMNode* _currentElement)
{
	INIT_LOG("mglSystem", "createDataLayer(DOMNode* _currentElement)");

	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >(_currentElement);

	DOMNodeList*      children = currentElement->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	mglDataSource* thisDS;

	XMLCh* TAG_DataSource = XMLString::transcode("DataSource");

	// For all nodes, children of "GUI" in the XML tree.
	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
			if ( XMLString::equals(currentElement->getTagName(), TAG_DataSource))
			{
				/* The XML should always contain the following tags at this point:
				 * <name>,<libname>, <classname> and <conf>
				 * The programmer can even replace the frame object implementation by using
				 * his own library at this point!
				 */

				DOMElement* DE_name = currentElement->getFirstElementChild();
				DOMElement* DE_libname = DE_name->getNextElementSibling();
				DOMElement* DE_classname = DE_libname->getNextElementSibling();

				DOMElement* DE_configuration = DE_classname->getNextElementSibling();

				/*
				 * Name is mandatory
				 */
				LOG_TRACE("Got DataSource named: " << XMLString::transcode(DE_name->getTextContent()) << " Classname: " << XMLString::transcode(DE_classname->getTextContent()));

				// Create the configured element via the factory

				mglValString* name = new mglValString(XMLString::transcode(DE_name->getTextContent()));
				mglValString* libname = new mglValString(XMLString::transcode(DE_libname->getTextContent()));
				mglValString* classname = new mglValString(XMLString::transcode(DE_classname->getTextContent()));

				thisDS = mglDataSourceManager::Inst().createDataSource(libname,
													classname,
													DE_configuration);
				m_DataSources.insert(pair<mglValString,mglDataSource*>(*name,thisDS));
			}
		}
	}

	XMLString::release(&TAG_DataSource);

	LOG_TRACE("Initializing data sources...");
	map<mglValString,mglDataSource*>::iterator itDS;
	for (itDS = m_DataSources.begin(); itDS != m_DataSources.end(); itDS++)
		itDS->second->init();
}


/**
 * Retrieve a datasource with the given name.
 * Application code should know the type as the retrieved object is a general mglDataSource pointer.
 * @param _name
 * @return
 */
mglDataSource* mglSystem::getDataSource(mglValString _name)
{
	mglDataSourceMap::iterator itDS = m_DataSources.find(_name);
	if (itDS == m_DataSources.end())
		return NULL;
	else
		return itDS->second;
}



void mglSystem::destroy()
{
	map<mglValString, mglDataSource*>::iterator itDS;
	for (itDS = m_DataSources.begin(); itDS != m_DataSources.end(); itDS++)
		itDS->second->deInit();

	mglLogger::Inst().destroy();
}

