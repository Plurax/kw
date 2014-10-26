
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
#include "mglValues/mglValCoord.h"

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
void mglSystem::init(void (*ptr)(void))
{
	m_libInfo = new mglLibraryInfo("mgl", "0.1", "Embedded GL Toolkit", "Christoph Romas",	"Proprietary - tbd");
	// Insert default factory into the list
	mglGuiLibManager& objManager = mglGuiLibManager::Inst();
	objManager.init();
	mglDataSourceManager& dsManager = mglDataSourceManager::Inst();
	dsManager.init();
	m_ContextAnimation = NULL;
	m_ValueEditor = NULL;
	m_ButtonDown = false;

	m_DraggingContext = NULL;

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

/**
 * Destructor - deletes all object lists.
 */
mglSystem::~mglSystem()
{
	uint uiIndex;
	for (uiIndex = 0; uiIndex < m_lMainFrames.size(); uiIndex++)
		delete m_lMainFrames.at(uiIndex); // delete the root frame objects
	m_lMainFrames.clear(); // clear all registered root frames

	for (uiIndex = 0; uiIndex < m_lMenus.size(); uiIndex++)
		delete m_lMenus.at(uiIndex); // delete the root frame objects
	m_lMenus.clear();

	for (uiIndex = 0; uiIndex < m_lEditors.size(); uiIndex++)
		delete m_lEditors.at(uiIndex); // delete the root frame objects
	m_lEditors.clear();
}


/**
 * Processes an input message.
 * An additional degree of freedom is implemented to allow a context menu to be opened at the touch position.
 * The context menu is also supported with IGR pressing, so you can implement context menus which can be selected via IGR.
 * @param Message
 * @return
 */
mglMessage* mglSystem::processInputMessage(mglInputMessage* Message)
{
	INIT_LOG("mglSystem", "processInputMessage(mglInputMessage* Message)");
	mglGuiObject* Target;

	// If the input message is a mouse or IGR press set the timer!
	if ((Message->getInputType() == eInputMouseButtonPress) ||
			(Message->getInputType() == eInputIGRPress))
	{
		m_ContextMenuTimer.start();
		m_ButtonDown = true;
	}

	// Clear the timer on button release
	if ((Message->getInputType() == eInputMouseButtonRelease) ||
			(Message->getInputType() == eInputIGRRelease))
	{
		m_ContextMenuTimer.end();
		timespec tmpTs = m_ContextMenuTimer.getDiffTime();
		m_ContextMenuTimer.clear();
		Message->setDiffTime(tmpTs);
		if ((unsigned long)tmpTs.tv_nsec + ((unsigned long)tmpTs.tv_sec * (unsigned long)1000000000) >= m_Configuration.getContextAnimationDelayEnd())
			Message->setContextTimeEnd(true);
		else
			Message->setContextTimeEnd(false);
		m_ButtonDown = false;
		delete m_ContextAnimation;
		m_ContextAnimation = NULL;
	}

	/**
	 * This will spawn an animatable object when the button press is longer than a configured value.
	 * This can be used to call the creation of a context menu.
	 * As we only allow one menu at a time, this can only be used by mainframes.
	 */
	if ((m_ButtonDown && (m_ContextMenuTimer.getCurrentDiffTime().tv_nsec >= m_Configuration.getContextAnimationDelayStart())) &&
			(m_ValueEditor == NULL) &&
			(m_CurrentMenu == NULL))
	{
		if (m_ContextAnimation == NULL)
		{
			m_ContextAnimation = mglGuiLibManager::Inst().createGUIObject(m_Configuration.getContextAnimationLib(),
					m_Configuration.getContextAnimationClass(), NULL);

			mglValCoord spawnCoord;
			if ((m_vSelectionContexts.back()->m_Focus != NULL) &&
					(!m_lastActionCausedByTouch))
			{
				spawnCoord = m_vSelectionContexts.back()->m_Focus->GetPosition();
			}
			else
				spawnCoord = Message->getCoord();

			m_ContextAnimation->SetPosition(spawnCoord);
		}
	}

	// Mouse button press and release cause search for the object and calling its processing functor
	if (Message->getInputType() == eInputMouseButtonPress)
	{
		m_lastActionCausedByTouch = true;

		Target = getTargetWindow(Message->getCoord());
		if (Target != NULL)
		{
			if ((Target->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableX)) ||
				(Target->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableY)))
			{
				m_DraggingContext = new mglDraggingContext;
				m_DraggingContext->m_DraggingObject = Target;
				m_DraggingContext->m_StartingObjectCoord = Target->GetPosition();
				m_DraggingContext->m_StartingCoord = Message->getCoord();
			}

			if (Target->getGuiAction() != NULL)
			{
				Message->setTarget(Target);

				return Target->ProcessMessage(Message);
			}
		}
	}

	if (Message->getInputType() == eInputMouseButtonRelease)
	{
		m_lastActionCausedByTouch = true;

		if (m_DraggingContext != NULL)
		{
			delete m_DraggingContext;
			m_DraggingContext = NULL;
		}
		else
		{
			Target = getTargetWindow(Message->getCoord());
			if (Target != NULL)
			{
				// If the target is editable we can open a corresponding editable dialog.
				if (Target->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Editable))
				{
					if (Message->getInputType() == eInputMouseButtonRelease)
					{
						if (m_ValueEditor == NULL)
						{
							// First we need to decide which editor has to be opened
							enumValType valType = Target->getValue()->getType();

							m_ValueEditor = m_lEditors.at(static_cast<unsigned long>(valType) - 1); // 0 is undefined - so decrement it

							/**
							 * If the user decides to use IGR instead of touch - we preload the editable to allow this.
							 * This could be used to do wide range with touch and fine tuning with IGR
							 * Attention - we dont use the focus here - and we will not return to it!
							 */
							m_vSelectionContexts.back()->m_Editing = Target;
							m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_SELECTED);

							if (0 == (m_ValueEditor->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_FixedEditor)))
							{
								mglValCoord spawnCoord;
								spawnCoord = Message->getCoord();
								// Correct the position if the editor would be clipped
								if (spawnCoord.m_fX + m_ValueEditor->GetWidth() > m_Configuration.getXRes())
								{
									spawnCoord.setX(m_Configuration.getXRes() - m_ValueEditor->GetWidth() - 1);
								}
								if (spawnCoord.m_fY < (m_ValueEditor->GetHeight() + 1))
								{
									spawnCoord.setY(1 + m_ValueEditor->GetHeight());
								}

								m_ValueEditor->SetPosition(spawnCoord);
							}
							m_ValueEditor->InitEditable(Target);
							LOG_TRACE("Opened editor");
						}
						else
						{
							// Hide the editor menu - this is used as "commit"
							m_vSelectionContexts.back()->m_Editing = NULL;
							m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);
							m_ValueEditor = NULL;
							LOG_TRACE("Closed editor");
						}
					}
				}
				else
				{
					if (Target->getGuiAction() != NULL)
					{
						Message->setTarget(Target);

						return Target->ProcessMessage(Message);
					}
				}
			}
			else
			{
				/**
				 * In this case - we cancel the input because the context editor was open but the user clicked aside of it
				 */
				if (m_ValueEditor != NULL)
				{
					m_ValueEditor = NULL;
					if (m_vSelectionContexts.back()->m_Focus != m_vSelectionContexts.back()->m_Editing)
						m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_STANDARD);
					else
						if (m_vSelectionContexts.back()->m_Focus == m_vSelectionContexts.back()->m_Editing)
								m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);

					m_vSelectionContexts.back()->m_Editing = NULL;
				}
			}
		}
	}

	if (Message->getInputType() == eInputMouseMove)
	{
		// In case of Mouse move we need to check if the mouse is already down and a dragging object is caught
		if (m_DraggingContext != NULL)
		{
			float xDiff = 0.0;
			float yDiff = 0.0;

			if (m_DraggingContext->m_DraggingObject->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableX))
				xDiff = m_DraggingContext->m_StartingCoord.m_fX - Message->getCoord().m_fX;

			if (m_DraggingContext->m_DraggingObject->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableY))
				yDiff = m_DraggingContext->m_StartingCoord.m_fY - Message->getCoord().m_fY;

			mglValCoord newCoord = mglValCoord(m_DraggingContext->m_StartingObjectCoord.m_fX, // + xDiff,
					m_DraggingContext->m_StartingObjectCoord.m_fY + yDiff,
					m_DraggingContext->m_StartingObjectCoord.m_fZ);

			// Limit the position to the drag limits of the object

			if (m_DraggingContext->m_DraggingObject->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableX))
			{
				if (newCoord.m_fX < m_DraggingContext->m_DraggingObject->getMinDragX())
					newCoord.m_fX = m_DraggingContext->m_DraggingObject->getMinDragX();
				if (newCoord.m_fX > m_DraggingContext->m_DraggingObject->getMaxDragX())
					newCoord.m_fX = m_DraggingContext->m_DraggingObject->getMaxDragX();
			}
			if (m_DraggingContext->m_DraggingObject->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableY))
			{
				if (newCoord.m_fY < m_DraggingContext->m_DraggingObject->getMinDragY())
					newCoord.m_fY = m_DraggingContext->m_DraggingObject->getMinDragY();
				if (newCoord.m_fY > m_DraggingContext->m_DraggingObject->getMaxDragY())
					newCoord.m_fY = m_DraggingContext->m_DraggingObject->getMaxDragY();
			}

			m_DraggingContext->m_DraggingObject->SetPosition(newCoord);

			/**
			 * Attention - now we check if an editor is opened - to realize modifications on the target object we call the edited
			 * value functor with the information editor object. The functor then can implement the modification of the values.
			 */
			if ((m_ValueEditor != NULL) && (m_vSelectionContexts.back()->m_Editing != NULL))
			{
				Message->setTarget(m_ValueEditor);
				Message->setEditedObject(m_vSelectionContexts.back()->m_Editing);

				/**
				 * This will send the movement message of the editor to the editor object
				 */
				m_ValueEditor->ProcessMessage(Message);
			}
		}
	}

	if (Message->getInputType() == eInputIGRRelease)
	{
		m_lastActionCausedByTouch = false;

		/**
		 * The user opened a touch editor but he committed with the IGR button
		 */
		if (m_ValueEditor != NULL)
		{
			if (m_DraggingContext != NULL)
			{
				//TODO: Call the process handler of the value object to allow reaction on commit (e.g. sending values to controller)
				m_DraggingContext = NULL;
			}
			m_ValueEditor = NULL;
			if (m_vSelectionContexts.back()->m_Focus != m_vSelectionContexts.back()->m_Editing)
				m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_STANDARD);
			else
				if (m_vSelectionContexts.back()->m_Focus == m_vSelectionContexts.back()->m_Editing)
						m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);

			m_vSelectionContexts.back()->m_Editing = NULL;
		}
		else
		if (m_vSelectionContexts.back()->m_Focus != NULL)
		{
			LOG_TRACE("Entering focus handler");
			if (!(m_vSelectionContexts.back()->m_Focus->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Editable)))
			{
				LOG_TRACE("Object is not editable");
				Message->setTarget(m_vSelectionContexts.back()->m_Focus);
				m_vSelectionContexts.back()->m_Focus->ProcessMessage(Message);
			}
			else
			{
				LOG_TRACE("Object is editable");
				if (m_vSelectionContexts.back()->m_Editing == NULL)
				{
					m_vSelectionContexts.back()->m_Editing = m_vSelectionContexts.back()->m_Focus;
					m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_SELECTED);
				}
				else
				{
					m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);
					m_vSelectionContexts.back()->m_Editing = NULL;
				}
			}
		}
	}

	if (Message->getInputType() == eInputIGR)
	{
		m_lastActionCausedByTouch = false;

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
				{
					pTemp = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->begin());
					while ((pTemp != NULL) && (!(pTemp->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Selectable))))
						pTemp = pTemp->next();
				}
				else
				{
					pTemp = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->rbegin());
					while ((pTemp != NULL) && (!(pTemp->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Selectable))))
						pTemp = pTemp->prev();
				}

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
					if (pTemp->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Selectable))
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
			// Editables are detected via the flag, but the functor has to implement the IGR count management
			Message->setTarget(m_vSelectionContexts.back()->m_Editing);
			mglMessage* retMsg =  m_vSelectionContexts.back()->m_Editing->ProcessMessage(Message);

			if (m_ValueEditor != NULL)
			{
				m_ValueEditor->setValue(m_vSelectionContexts.back()->m_Editing->getValue());
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
	glTranslatef(0.0, 0.0, 0.1); // Menu layer is translated one unit onto the user (we are in projection - this will not cause zoom)

	if (m_CurrentMenu != NULL)
		m_CurrentMenu->Draw();

	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.2); // Menu layer is translated one unit onto the user (we are in projection - this will not cause zoom)

	if (m_ContextAnimation != NULL)
		m_ContextAnimation->Draw();

	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.3); // Menu layer is translated one unit onto the user (we are in projection - this will not cause zoom)

	if (m_ValueEditor != NULL)
		m_ValueEditor->Draw();

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
	mglValCoord coord;
	destination = m_ValueEditor; // set target to non IGR editor object (keyboard, slider etc)

	if (destination != NULL)
	{

		// then search within the concatenation for the final input target
		coord = (m_ValueEditor)->calcPosition();
		if ((pt.m_fX >= coord.m_fX) &&
			(pt.m_fX < (coord.m_fX + (m_ValueEditor)->GetWidth())) &&
			(pt.m_fY <= coord.m_fY) &&
			(pt.m_fY > (coord.m_fY - (m_ValueEditor)->GetHeight())))
		{
			destination = m_ValueEditor->getChildAtPosition(pt);
			return destination;
		}
		return NULL; /** A context editor menu is modal - if we press aside of it - we cancel the input */
	}

	destination = m_CurrentMenu; // set target to current menu if not null

	if (destination != NULL)
	{
		if (destination->isVisible())
		{
			// then search within the concatenation for the final input target
			coord = (m_CurrentMenu)->calcPosition();
			if ((pt.m_fX >= coord.m_fX) &&
				(pt.m_fX < (coord.m_fX + (m_CurrentMenu)->GetWidth())) &&
				(pt.m_fY <= coord.m_fY) &&
				(pt.m_fY > (coord.m_fY - (m_CurrentMenu)->GetHeight())))
			{
				destination = m_CurrentMenu->getChildAtPosition(pt);
				return destination;
			}
		}
	}

	destination = m_CurrentMainFrame; // set target to current root mainframe
	if (!destination->isVisible())
		return 0;

	coord = (m_CurrentMainFrame)->calcPosition();
	// then search within the concatenation for the final input target
	if ((pt.m_fX >= coord.m_fX) &&
		(pt.m_fX < (coord.m_fX + (m_CurrentMainFrame)->GetWidth())) &&
		(pt.m_fY <= coord.m_fY) &&
		(pt.m_fY > (coord.m_fY - (m_CurrentMainFrame)->GetHeight())))
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

void mglSystem::openMenu(mglGuiObject *Menu, mglValCoord _coord)
{
	m_vSelectionContexts.push_back(new mglSelectionContext());

	m_CurrentMenu = Menu;
	if (!_coord.empty())
		Menu->SetPosition(_coord);
	m_vSelectionContexts.back()->m_SelectListParent = m_CurrentMenu;
	mglGuiObject* obj = NULL;

	if (!m_lastActionCausedByTouch)
	{
		m_vSelectionContexts.back()->m_pCurrentSelectionList = m_CurrentMenu->getChildren();
		mglGuiObjectList::iterator it = m_vSelectionContexts.back()->m_pCurrentSelectionList->begin();
		for (; it != m_vSelectionContexts.back()->m_pCurrentSelectionList->end(); it++)
		{
			obj = *it;
			if (obj->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Selectable))
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
   XMLCh* TAG_Editors = XMLString::transcode("EDITORS");
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
					createGUIfromXML(currentNode, NULL, NULL, m_lMainFrames, 0);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_Menus))
				{
					createGUIfromXML(currentNode, NULL, NULL, m_lMenus, 1);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_Editors))
				{
					createGUIfromXML(currentNode, NULL, NULL, m_lEditors, 2);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_Fonts))
				{
					m_FontProvider->loadFonts(currentNode);
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_Textures))
				{
					m_TextureManager->initTextures(currentNode);
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
      XMLString::release(&TAG_Editors);
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
 * @param listToAdd - pointer to the list where root objects will be added
 */
void mglSystem::createGUIfromXML(DOMNode* GUIELement, mglGuiObject* parent, mglGuiObject* prev, mglGuiObjectList& listToAdd, int _listtype)
{
	INIT_LOG("mglSystem", "createGUIfromXML(DOMNode* GUIELement, mglGuiObject* parent, mglGuiObject* prev)");

	DOMNodeList*      children = GUIELement->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	mglGuiObject* thisWindow = NULL;
	mglGuiObject* prevWindow = NULL;

	XMLCh* TAG_mglWindowItem = XMLString::transcode("mglWindowItem");
	XMLCh* TAG_name = XMLString::transcode("name");
	XMLCh* TAG_libname = XMLString::transcode("libname");
	XMLCh* TAG_classname = XMLString::transcode("classname");
	XMLCh* TAG_handlerLib = XMLString::transcode("handlerLib");
	XMLCh* TAG_handlerClass = XMLString::transcode("handlerClass");
	XMLCh* TAG_config = XMLString::transcode("config");
	XMLCh* TAG_children = XMLString::transcode("children");

	mglValString* name = NULL;
	mglValString* libname = NULL;
	mglValString* classname = NULL;
	mglValString* handlerlibname = NULL;
	mglValString* handlerclassname = NULL;

	DOMElement* DE_configuration;
	DOMElement* DE_children;

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
				DOMNodeList*      configchildren = currentElement->getChildNodes();
				const  XMLSize_t configchildrenCount = configchildren->getLength();


				for( XMLSize_t xx = 0; xx < configchildrenCount; ++xx )
				{
					DOMNode* configSubNode = configchildren->item(xx);
					if( configSubNode->getNodeType() &&  // true is not NULL
							configSubNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
					{
						// Found node which is an Element. Re-cast node as element
						DOMElement* configCurrentElement
									= dynamic_cast< xercesc::DOMElement* >( configSubNode );

						if ( XMLString::equals(configCurrentElement->getTagName(), TAG_name))
						{
							name = new mglValString(XMLString::transcode(configCurrentElement->getTextContent()));
						}

						if ( XMLString::equals(configCurrentElement->getTagName(), TAG_libname))
						{
							libname = new mglValString(XMLString::transcode(configCurrentElement->getTextContent()));
						}

						if ( XMLString::equals(configCurrentElement->getTagName(), TAG_classname))
						{
							classname = new mglValString(XMLString::transcode(configCurrentElement->getTextContent()));
						}

						if ( XMLString::equals(configCurrentElement->getTagName(), TAG_handlerLib))
						{
							handlerlibname = new mglValString(XMLString::transcode(configCurrentElement->getTextContent()));
						}

						if ( XMLString::equals(configCurrentElement->getTagName(), TAG_handlerClass))
						{
							handlerclassname = new mglValString(XMLString::transcode(configCurrentElement->getTextContent()));
						}

						if ( XMLString::equals(configCurrentElement->getTagName(), TAG_config))
						{
							DE_configuration = configCurrentElement;
						}

						if ( XMLString::equals(configCurrentElement->getTagName(), TAG_children))
						{
							DE_children= configCurrentElement;
						}
					}

				}


				// Check for attributes
				if (_listtype == 0) // mainframes
				{

				}
				if (_listtype == 1) // menus
				{

				}
				if (_listtype == 2) // editors
				{
					XMLCh* ATTR_valtype = XMLString::transcode("valtype");
					const XMLCh* windowitem_attr = currentElement->getAttribute(ATTR_valtype);
					mglValString* str_valtype = new mglValString(XMLString::transcode(windowitem_attr));
					LOG_TRACE("Attribute: valtype is " << str_valtype->str()->c_str());
				}


				/*
				 * Name is mandatory
				 */
				LOG_TRACE("Got GUI Element named: " << name->str()->c_str());
				LOG_TRACE("Got GUI Element libname: " << libname->str()->c_str());
				LOG_TRACE("Got GUI Element classname: " << classname->str()->c_str());

				// Create the configured element via the factory
				thisWindow = mglGuiLibManager::Inst().createGUIObject(libname,
													classname,
													DE_configuration);

				/* If one of both strings is NULL connect the functor to NULL, otherwise its possible to create functors within the
				 * 				constructor of the guiobject without using XML configuration
				 */
				if ((handlerlibname != NULL) && (handlerclassname != NULL))
				{
					if ((handlerlibname->str()->compare("NULL") == 0) || (handlerclassname->str()->compare("NULL") == 0))
					{
						thisWindow->Connect(NULL);
						LOG_TRACE("Connected NULL");
					}
					else
					{
						// After we created the object we can attach the handler if it exists
						mglGuiActionFunctor* funct = mglGuiLibManager::Inst().createGuiAction(handlerlibname, handlerclassname);
						thisWindow->Connect(funct);
					}
				}

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
					createGUIfromXML(DE_children, thisWindow, NULL, listToAdd, _listtype);
				}
				prevWindow = thisWindow;

				// Clear temp strings
				if (name != NULL)
				{
					delete name;
					name = NULL;
				}
				if (libname != NULL)
				{
					delete libname;
					libname = NULL;
				}
				if (classname != NULL)
				{
					delete classname;
					classname = NULL;
				}
				if (handlerlibname != NULL)
				{
					delete handlerlibname;
					handlerlibname = NULL;
				}
				if (handlerclassname != NULL)
				{
					delete handlerclassname;
					handlerclassname = NULL;
				}
			}
		}

	}
	XMLString::release(&TAG_mglWindowItem);
	XMLString::release(&TAG_name);
	XMLString::release(&TAG_libname);
	XMLString::release(&TAG_classname);
	XMLString::release(&TAG_handlerLib);
	XMLString::release(&TAG_handlerClass);
	XMLString::release(&TAG_config);
	XMLString::release(&TAG_children);
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



mglGuiObject* mglSystem::getValueEditor()
{
	return m_ValueEditor;
}

mglGuiObject* mglSystem::getEditedObject()
{
	return m_vSelectionContexts.back()->m_Editing;
}
