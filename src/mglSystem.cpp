
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

#include "mglSystem.h"
#include "mglDebug/mglTechnicalException.h"
#include "mglValues/mglValCoord.h"

using namespace std;

mglSystem::mglSystem()
{
}

/**
 * Main initialization routine.
 * Regard that XercesC needs a set locale to create a correct char transcoder engine. This
 * should be done in the main executable to allow multiple encodings. Xerces will then create
 * the correct transcoder engine and will support e.g. custom chars for unicode points of the XML correctly.
 *
 * @param ptr - flushGL function pointer which is called by Draw after rendering.
 */
void mglSystem::init(void(*ptr)(), mglValString& configfile)
{
	/* Note this is not used as shared pointer as we use this inforation within lib handles which 
	   are propably initialized with external shared lib factories!
	*/
	m_libInfo = new mglLibraryInfo("mgl", "0.2", "Embedded GL Toolkit", "Christoph Romas",	"MIT - www.electroknit.io");

	if (ptr != NULL)
	{
		// Insert default factory into the list
		mglGuiLibManager& objManager = mglGuiLibManager::Inst();
		objManager.init();
		flushGL = ptr;
	}
	mglDataSourceManager& dsManager = mglDataSourceManager::Inst();
	dsManager.init();
	m_ContextAnimation = nullptr;
	m_ValueEditor = nullptr;
	m_ButtonDown = false;

	m_DraggingContext = nullptr;

	if (ptr != NULL)
	{
		m_FontProvider = make_shared<mglFontProvider>();
		m_TextureManager = make_shared<mglTextureManager>();
		m_vSelectionContexts.push_back(make_shared<mglSelectionContext>());
	}

	readConfiguration(configfile);

	m_CurrentMainFrame = nullptr;
	m_CurrentMenu = nullptr;

	m_lastActionCausedByTouch = false;
}

/**
 * Destructor - deletes all object lists.
 */
mglSystem::~mglSystem()
{
	std::map<mglValString, shared_ptr<mglGuiObject>>::iterator it;
	it = m_mMainFrames.begin();
	while (it != m_mMainFrames.begin())
	{
		m_mMainFrames.erase(it);
		it--;
	}

	it = m_mMenus.begin();
	while (it != m_mMenus.begin())
	{
		m_mMenus.erase(it);
		it--;
	}

	it = m_mEditors.begin();
	while (it != m_mEditors.begin())
	{
		m_mEditors.erase(it);
		it--;
	}

}


/**
 * Processes an input message.
 * An additional degree of freedom is implemented to allow a context menu to be opened at the touch position.
 * The context menu is also supported with IGR pressing, so you can implement context menus which can be selected via IGR.
 * @param Message
 * @return
 */
shared_ptr<mglMessage> mglSystem::processInputMessage(shared_ptr<mglInputMessage> Message)
{
	INIT_LOG("mglSystem", "processInputMessage(shared_ptr<mglInputMessage> Message)");
	shared_ptr<mglGuiObject> Target;

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
		boost::posix_time::time_duration tmpTs = m_ContextMenuTimer.getDiffTime();
		m_ContextMenuTimer.clear();
		Message->setDiffTime(tmpTs);
		if (tmpTs >= m_Configuration.getContextAnimationDelayEnd())
			Message->setContextTimeEnd(true);
		else
			Message->setContextTimeEnd(false);
		m_ButtonDown = false;
		m_ContextAnimation = nullptr;
	}

	/**
	 * This will spawn an animatable object when the button press is longer than a configured value.
	 * This can be used to call the creation of a context menu.
	 * As we only allow one menu at a time, this can only be used by mainframes.
	 */
	if ((m_ButtonDown && (m_ContextMenuTimer.getCurrentDiffTime() >= m_Configuration.getContextAnimationDelayStart())) &&
			(!m_ValueEditor) &&
			(!m_CurrentMenu))
	{
		if (!m_ContextAnimation)
		{
			m_ContextAnimation = shared_ptr<mglGuiObject>(mglGuiLibManager::Inst().createGUIObject(m_Configuration.getContextAnimationLib(),
																								   m_Configuration.getContextAnimationClass(), NULL));

			mglValCoord spawnCoord;
			if ((m_vSelectionContexts.back()->m_Focus) &&
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
		if (Target)
		{
			if ((Target->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableX)) ||
				(Target->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_DraggableY)))
			{
				m_DraggingContext = shared_ptr<mglDraggingContext>(new mglDraggingContext);
				m_DraggingContext->m_DraggingObject = Target;
				m_DraggingContext->m_StartingObjectCoord = Target->GetPosition();
				m_DraggingContext->m_StartingCoord = Message->getCoord();
			}

			if (Target->getGuiAction() != nullptr)
			{
				Message->setTarget(Target);

				return Target->ProcessMessage(Message);
			}
		}
	}

	if (Message->getInputType() == eInputMouseButtonRelease)
	{
		m_lastActionCausedByTouch = true;

		if (m_DraggingContext)
		{
			m_DraggingContext.reset();
		}
		else
		{
			Target = getTargetWindow(Message->getCoord());
			if (Target)
			{
				// clear an active focus
				if ((m_vSelectionContexts.back()->m_Focus != nullptr) && (m_vSelectionContexts.back()->m_Focus != Target))
				{
					m_vSelectionContexts.back()->m_Focus->setState(OBJ_STATE_STANDARD);
				}

				// If the target is editable we can open a corresponding editable dialog.
				if (Target->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Editable))
				{
					if (Message->getInputType() == eInputMouseButtonRelease)
					{
						if (!m_ValueEditor)
						{
							/** First we need to decide which editor has to be opened
							 *
							 * Therefore we retrieve the value of the object and construct a name string of the class via RTTI
							 * This information is used to open the default editor, which is configured in the XML.
							 *
							 * To allow usage of different editors, each mglGuiObject can set its own editor name via its
							 * configuration. This editor is also defined in the xml configuration.
							 */
							mglValString valType = Target->getEditorName();
							if (valType.empty() || valType.size() == 0)
							{
								int status;
								const std::type_info &ti = typeid(*(Target->getValue()));
#ifdef WIN32
								const char* realname = ti.name();
								valType = mglValString(realname);
#else
								char* realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
								valType = mglValString(realname);
								free (realname);
#endif

							}

							// Use the standard editor
							mglGuiObjectMap::iterator findIt = m_mEditors.find(valType);
							if (findIt == m_mEditors.end())
							{
								THROW_TECHNICAL_EXCEPTION(876, "Error while retrieving editor. \"" << valType.str()->c_str() << "\" does not exist!");
							}
							m_ValueEditor = findIt->second;

							/**
							 * If the user decides to use IGR instead of touch - we preload the editable to allow this.
							 * This could be used to do wide range with touch and fine tuning with IGR
							 * Attention - we dont use the focus here - and we will not return to it!
							 */
							m_vSelectionContexts.back()->m_Editing = Target;
//							m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_SELECTED);

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
							m_vSelectionContexts.back()->m_Editing = nullptr;
							m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);
							m_ValueEditor = nullptr;
							LOG_TRACE("Closed editor");
						}
					}
				}
				else
				{
					if (Target->getGuiAction())
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
				if (m_ValueEditor)
				{
					m_ValueEditor = nullptr;
					if (m_vSelectionContexts.back()->m_Focus != m_vSelectionContexts.back()->m_Editing)
						m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_STANDARD);
					else
						if (m_vSelectionContexts.back()->m_Focus == m_vSelectionContexts.back()->m_Editing)
								m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);

					m_vSelectionContexts.back()->m_Editing = nullptr;
				}
			}
		}
	}

	if (Message->getInputType() == eInputMouseMove)
	{
		// In case of Mouse move we need to check if the mouse is already down and a dragging object is caught
		if (m_DraggingContext)
		{
			float yDiff = 0.0;
			float xDiff = 0.0;

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
			if ((m_ValueEditor) && (m_vSelectionContexts.back()->m_Editing))
			{
				Message->setTarget(m_ValueEditor);
				Message->setEditedObject(m_vSelectionContexts.back()->m_Editing);

				/**
				 * This will send the movement message of the editor to the editor object
				 */
				
				m_ValueEditor->ProcessMessage(Message);
			}
			else
			{
				/**
				 * In this case we assume that the mainframe directly contains sliders which are used here.
				 * So we send the message to the dragged object itself.
				 * But this means that we can not know which object is edited. This needs to be handled within the handler.
				 */
				Message->setTarget(m_DraggingContext->m_DraggingObject);
				m_DraggingContext->m_DraggingObject->ProcessMessage(Message);
			}
		}
	}

	if (Message->getInputType() == eInputIGRRelease)
	{
		m_lastActionCausedByTouch = false;

		/**
		 * The user opened a touch editor but he committed with the IGR button
		 */
		if (m_ValueEditor)
		{
			if (m_DraggingContext)
			{
				//TODO: Call the process handler of the value object to allow reaction on commit (e.g. sending values to controller)
				m_DraggingContext = nullptr;
			}
			m_ValueEditor = nullptr;
			if (m_vSelectionContexts.back()->m_Focus != m_vSelectionContexts.back()->m_Editing)
				m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_STANDARD);
			else
				if (m_vSelectionContexts.back()->m_Focus == m_vSelectionContexts.back()->m_Editing)
						m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);

			m_vSelectionContexts.back()->m_Editing = nullptr;
		}
		else
		if (m_vSelectionContexts.back()->m_Focus != nullptr)
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
				if (m_vSelectionContexts.back()->m_Editing == nullptr)
				{
					m_vSelectionContexts.back()->m_Editing = m_vSelectionContexts.back()->m_Focus;
					m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_SELECTED);
				}
				else
				{
					m_vSelectionContexts.back()->m_Editing->setState(OBJ_STATE_FOCUSSED);
					m_vSelectionContexts.back()->m_Editing = nullptr;
				}
			}
		}
	}

	if (Message->getInputType() == eInputIGR)
	{
		m_lastActionCausedByTouch = false;

		// we are in focus level - step through the selection list
		if (m_vSelectionContexts.back()->m_Editing == nullptr)
		{
			shared_ptr<mglGuiObject> pTemp = nullptr;
			shared_ptr<mglGuiObject> pSwap = nullptr;

			int iCount = Message->getIGRCount();
			bool bForward,bEntry = false;

			if (iCount > 0)
				bForward = true;
			else
			{
				bForward = false;
				iCount *= -1;
			}

			if (m_vSelectionContexts.back()->m_pCurrentSelectionList == nullptr)
			{
				bEntry = true;
				m_vSelectionContexts.back()->m_pCurrentSelectionList = m_vSelectionContexts.back()->m_SelectListParent->getChildren();
				if (bForward)
				{
					pTemp = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->begin());
					while ((pTemp != nullptr) && (!(pTemp->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Selectable))))
						pTemp = pTemp->next();
				}
				else
				{
					pTemp = *(m_vSelectionContexts.back()->m_pCurrentSelectionList->rbegin());
					while ((pTemp != nullptr) && (!(pTemp->getOptionMask() & static_cast<unsigned long>(enumObjectFlags::Obj_Selectable))))
						pTemp = pTemp->prev();
				}

			}
			else
			{
				pTemp = m_vSelectionContexts.back()->m_Focus;
				m_vSelectionContexts.back()->m_Focus->setState(OBJ_STATE_STANDARD);
			}

			while ((iCount != 0) && (pTemp != nullptr))
			{
				if (!bEntry)
				{
					if (bForward)
						pSwap = pTemp->next();
					else
						pSwap = pTemp->prev();

					if (pSwap == nullptr) // reached end of concatenation
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

			if (pTemp != nullptr)
			{
				pTemp->setState(OBJ_STATE_FOCUSSED);
				m_vSelectionContexts.back()->m_Focus = pTemp;
			}
			else
			{
				m_vSelectionContexts.back()->m_Focus = nullptr;
				m_vSelectionContexts.back()->m_pCurrentSelectionList = nullptr;
			}
		}
		else
		{
			// Editables are detected via the flag, but the functor has to implement the IGR count management
			Message->setTarget(m_vSelectionContexts.back()->m_Editing);
			auto retMsg =  m_vSelectionContexts.back()->m_Editing->ProcessMessage(Message);

			if (m_ValueEditor != nullptr)
			{
				m_ValueEditor->setValue(m_vSelectionContexts.back()->m_Editing->getValue());
			}
		}
	}

	return nullptr;
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

	if (m_CurrentMenu != nullptr)
		m_CurrentMenu->Draw();

	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.2); // Menu layer is translated one unit onto the user (we are in projection - this will not cause zoom)

	if (m_ContextAnimation != nullptr)
		m_ContextAnimation->Draw();

	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.3); // Menu layer is translated one unit onto the user (we are in projection - this will not cause zoom)

	if (m_ValueEditor != nullptr)
		m_ValueEditor->Draw();

	(*flushGL)();

}


shared_ptr<mglGuiObject> mglSystem::getGuiObject(mglValString _str)
{
	std::map<mglValString, shared_ptr<mglGuiObject>>::iterator findIt = m_mGuiObjects.find(_str);
	if (findIt == m_mGuiObjects.end())
		return nullptr;
	else
		return findIt->second;
}


/**
 * Determine the gui object which is at the given coordinates.
 * This function regards mainframes and menus. Only visible marked objects are regarded.
 * @param pt
 * @return
 */
shared_ptr<mglGuiObject> mglSystem::getTargetWindow(mglValCoord pt)
{
	shared_ptr<mglGuiObject> destination = m_ValueEditor; // set target to non IGR editor object (keyboard, slider etc);
	mglValCoord coord;

	if (destination != nullptr)
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
		return nullptr; /** A context editor menu is modal - if we press aside of it - we cancel the input */
	}

	destination = m_CurrentMenu; // set target to current menu if not null

	if (destination != nullptr)
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
		return nullptr;

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

	return nullptr;
}

shared_ptr<mglGuiObject> mglSystem::getMainFrame(mglValString name)
{
	mglGuiObjectMap::iterator it = m_mMainFrames.find(name);
	if (it == m_mMainFrames.end())
	{
		INIT_LOG("mglSystem", "getMainFrame");
		THROW_TECHNICAL_EXCEPTION(876, "Error while retrieving main frame. " << name.str()->c_str() << " Does not exist!");
	}
	shared_ptr<mglGuiObject> retval = it->second;
	return retval;
}

shared_ptr<mglGuiObject> mglSystem::getMenu(mglValString name)
{
	mglGuiObjectMap::iterator it = m_mMenus.find(name);
	if (it == m_mMenus.end())
	{
		INIT_LOG("mglSystem", "getMenu");
		THROW_TECHNICAL_EXCEPTION(876, "Error while retrieving menu. " << name.str()->c_str() << " Does not exist!");
	}
	shared_ptr<mglGuiObject> retval = it->second;
	return retval;
}

/**
 * Sets the mainframe to be shown.
 * This also will change the first selection context object to the newly set frame!
 * This behaviour allows changing main frames out of menus.
 * @param MainFrame
 */
void mglSystem::SetMainFrame(shared_ptr<mglGuiObject> MainFrame)
{
	m_CurrentMainFrame = MainFrame;
	m_vSelectionContexts.front()->m_pCurrentSelectionList = nullptr;

	m_vSelectionContexts.front()->m_SelectListParent = m_CurrentMainFrame;
}

void mglSystem::openMenu(shared_ptr<mglGuiObject> Menu, mglValCoord _coord)
{
	m_vSelectionContexts.push_back(shared_ptr<mglSelectionContext>(new mglSelectionContext()));

	m_CurrentMenu = Menu;
	if (!_coord.empty())
		Menu->SetPosition(_coord);
	m_vSelectionContexts.back()->m_SelectListParent = m_CurrentMenu;
	shared_ptr<mglGuiObject> obj = nullptr;

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
		m_vSelectionContexts.back()->m_pCurrentSelectionList = nullptr;

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
		m_vSelectionContexts.pop_back();
	}
	m_CurrentMenu = nullptr;
}


/**
 * This will return from the currently opened menu to the previous one.
 * If there was no menu opened before this one, same is done as in close...
 */
void mglSystem::returnFromMenu()
{
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
		mglLogger::Inst().configure(config["Logging"]);
		m_Configuration.init(config["AppConfiguration"]);
		createDataLayer(config["DataLayer"]);
		createGUIfromJSON(config["GUI"], nullptr, nullptr, m_mMainFrames, 0);
		createGUIfromJSON(config["MENUS"], nullptr, nullptr, m_mMenus, 1);
		createGUIfromJSON(config["EDITORS"], nullptr, nullptr, m_mEditors, 2);
		m_FontProvider->loadFonts(config["Font"]);
		setMessageHandlers(config["MessageHandlers"]);
		m_TextureManager->initTextures(config["Textures"]);
	}
	catch (mglTechnicalException& e)
	{
		LOG_EXCEPTION(e.getMessage());
	}
	catch (exception& e)
	{
		LOG_EXCEPTION("Exception occured during init!: " << e.what());
	}
}

/**
 *
 * @param GUIELement - GUI Tag (root element for gui definition)
 * @param parent - parent element for recursive usage
 * @param prev - previous element for recursive usage
 * @param listToAdd - pointer to the list where root objects will be added
 */
void mglSystem::createGUIfromJSON(json GUIElement, shared_ptr<mglGuiObject> parent, shared_ptr<mglGuiObject> prev, mglGuiObjectMap& listToAdd, int _listtype)
{
	INIT_LOG("mglSystem", "createGUIfromJSON(json GUIElement, shared_ptr<mglGuiObject> parent, shared_ptr<mglGuiObject> prev, mglGuiObjectMap& listToAdd, int _listtype)");

	shared_ptr<mglGuiObject> thisWindow = nullptr;
	shared_ptr<mglGuiObject> prevWindow = nullptr;

	shared_ptr<mglValString> name = nullptr;
	shared_ptr<mglValString> libname = nullptr;
	shared_ptr<mglValString> classname = nullptr;
	shared_ptr<mglValString> handlerlibname = nullptr;
	shared_ptr<mglValString> handlerclassname = nullptr;
	shared_ptr<mglValString> editorname = nullptr;

	json configuration;
	json children;

	for (auto& element : GUIElement["mglWindowItem"])
	{
		LOG_TRACE("Caught Window Item");
        /*
		 * The JSON should always contain the following tags at this point:
		 * <name>,<libname>, <classname>, <handlerLib>, <handlerClass> and <configuration>
		 * The programmer can even replace the frame object implementation by using
		 * his own library at this point!
		 */

		if (element.count("name"))
			name = make_shared<mglValString>(((element["name"])).get<string>());
		if (element.count("libname"))
			libname = make_shared<mglValString>(((element["libname"])).get<string>());
		if (element.count("classname"))
			classname = make_shared<mglValString>(((element["classname"])).get<string>());
		if (element.count("handlerLib"))
			handlerlibname = make_shared<mglValString>(((element["handlerLib"])).get<string>());
		if (element.count("handlerClass"))
			handlerclassname = make_shared<mglValString>(((element["handlerClass"])).get<string>());
		if (element.count("editorName"))
			editorname = make_shared<mglValString>(((element["editorName"])).get<string>());
		if (element.count("config"))
			configuration = element["config"];

		if (element.count("children"))
			children = element["children"];

		// Check for attributes
		if (_listtype == 0) // mainframes
		{

		}
		if (_listtype == 1) // menus
		{

		}
		if (_listtype == 2) // editors
		{
/*			XMLCh* ATTR_valtype = XMLString::transcode("valtype");
			const XMLCh* windowitem_attr = currentElement->getAttribute(ATTR_valtype);
			mglValString* str_valtype = new mglValString(XMLString::transcode(windowitem_attr));
			LOG_TRACE("Attribute: valtype is " << str_valtype->str()->c_str());
*/
		}

		LOG_TRACE("Got GUI Element named: " << *name);
		LOG_TRACE("Got GUI Element libname: " << *libname);
		LOG_TRACE("Got GUI Element classname: " << *classname);
		
		// Create the configured element via the factory
		thisWindow = mglGuiLibManager::Inst().createGUIObject(libname,
															  classname,
															  configuration);
		LOG_TRACE("Create performed...: " << *classname);
		
		// The custom editor setting is optional - we check if this tag was set and set the editor afterwards
		if (editorname)
		{
			thisWindow->setEditor(editorname);
			editorname = nullptr;
		}
		
		/* If one of both strings is NULL connect the functor to NULL, otherwise its possible to create functors within the
		 * 				constructor of the guiobject without using XML configuration
		 */

		if ((handlerlibname) && (handlerclassname))
		{
			if ((handlerlibname->str()->compare("NULL") == 0) || (handlerclassname->str()->compare("NULL") == 0))
			{
				thisWindow->Connect(nullptr);
				LOG_TRACE("Connected NULL");
			}
			else
			{
				// After we created the object we can attach the handler if it exists
				shared_ptr<mglMessageHandler> funct = mglGuiLibManager::Inst().createMessageHandler(handlerlibname, handlerclassname);
				thisWindow->Connect(funct);
			}
		}
		
		// A created gui object is also registered by its name
		m_mGuiObjects.insert(std::pair<mglValString, shared_ptr<mglGuiObject>>(mglValString(*name),thisWindow));

		/* Init Children of currently created object - this is a workaround for shared_from_this in constructor - as we dont want
		 * to use raw pointers anymore. With this you can create your own objects and let them initialize further children
		 * with out config in the JSON. This should be useful e.g. for keypads or objects with many children you dont want to 
		 * describe within the config.
		 */
		thisWindow->initChildren();

		// We are at parent level - so this is a main frame
		if (parent == nullptr)
			listToAdd.insert(std::pair<mglValString, shared_ptr<mglGuiObject>>(mglValString(*name), thisWindow));
		else
		{
			thisWindow->setParentWindow(parent);
			parent->AddChild(thisWindow);
		}

		thisWindow->setPrevWindow(prevWindow);
		thisWindow->setNextWindow(nullptr);
		if (prevWindow)
			prevWindow->setNextWindow(thisWindow);

		// Now ascend down and create the children
		if (children.size() > 0)
		{
			LOG_TRACE("Creating children for \"" << *name << "\"...");
			createGUIfromJSON(children, thisWindow, nullptr, listToAdd, _listtype);
		}
		prevWindow = thisWindow;

		// Clear temp strings
		name = nullptr;
		libname = nullptr;
		classname = nullptr;
		handlerlibname = nullptr;
		handlerclassname = nullptr;
	}
}

/**
 * This will configure the message handlers to be assigned on the different message IDs.
 * This is completely flexible to provide own handlers. The only handler which is intern
 * is the GUI Message for inputs with ID 0.
 *
 * @param _currentElement
 */
void mglSystem::setMessageHandlers(json messageconfig)
{
	INIT_LOG("mglSystem", "setMessageHandlers(json messageconfig)");

	int messageId = -1; // -1 is initial faulty - 0 is forbidden (internal gui messages)
	shared_ptr<mglValString> handlerlibname = nullptr;
	shared_ptr<mglValString> handlerclassname = nullptr;
	shared_ptr<string> msgID_str = nullptr;

	if (messageconfig == nullptr)
	{
		LOG_INFO("No message handlers found in config...");
		return;
	}
	else
		LOG_TRACE("Initializing message handlers...");

	for (auto& element : messageconfig)
	{

		handlerlibname = make_shared<mglValString>(((element["handlerLib"])).get<string>());
		handlerclassname = make_shared<mglValString>(((element["handlerClass"])).get<string>());
		msgID_str = make_shared<string>(((element["MessageId"])).get<string>());
		messageId = atoi(msgID_str->c_str());;

		/* Now create the message handler from the lib and attach it onto the ID
		 */
		if (handlerlibname != nullptr && handlerclassname != nullptr && msgID_str != nullptr)
		{
			// After we created the object we can attach the handler if it exists
			LOG_TRACE("Got a configured handler library: " << handlerlibname << " class: " << handlerclassname << " MessageID: " << messageId); 
			shared_ptr<mglMessageHandler> funct = mglGuiLibManager::Inst().createMessageHandler(handlerlibname, handlerclassname);
			m_mMessageHandlers.insert(std::pair<int, shared_ptr<mglMessageHandler>>(messageId,funct));
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
void mglSystem::createDataLayer(json _currentElement)
{
	INIT_LOG("mglSystem", "createDataLayer(json _currentElement)");

	shared_ptr<mglDataSource> thisDS;

	LOG_TRACE("Loading and initializing data sources...");

	for (json::iterator it = _currentElement.begin(); it != _currentElement.end(); ++it) 
	{
		if ( it.key() == "DataSource")
		{
			/* The XML should always contain the following tags at this point:
			 * <name>,<libname>, <classname> and <conf>
			 * The programmer can even replace the frame object implementation by using
			 * his own library at this point!
			 */

			auto name = make_shared<mglValString>(((*it)["name"]).get<string>());
			auto libname = make_shared<mglValString>(((*it)["libname"]).get<string>());
			auto classname = make_shared<mglValString>(((*it)["classname"]).get<string>());

			auto configuration = (*it)["configuration"];

			// Create the configured element via the factory

			thisDS = mglDataSourceManager::Inst().createDataSource(libname,
																   classname,
																   configuration);
			if (thisDS)
				m_DataSources.insert(pair<mglValString, shared_ptr<mglDataSource>>(*name,thisDS));

			thisDS = nullptr; // Kill local reference
		}
	}

	map<mglValString, shared_ptr<mglDataSource>>::iterator itDS;
	for (itDS = m_DataSources.begin(); itDS != m_DataSources.end(); itDS++)
		itDS->second->init();
	LOG_TRACE("Data sources completed...");
}


/**
 * Retrieve a datasource with the given name.
 * Application code should know the type as the retrieved object is a general mglDataSource pointer.
 * @param _name
 * @return
 */
shared_ptr<mglDataSource> mglSystem::getDataSource(mglValString _name)
{
	mglDataSourceMap::iterator itDS = m_DataSources.find(_name);
	if (itDS == m_DataSources.end())
		return nullptr;
	else
		return itDS->second;
}


/**
 * This function will process all events. This is used to allow separate event handlings,
 * for example for socket command reception etc. GUI Input events are also handled here.
 *
 */
void mglSystem::processEvents()
{
	INIT_LOG("mglSystem", "processEvents()");

	while (!m_MessageQueue.empty())
	{
		shared_ptr<mglMessage> processing = m_MessageQueue.front();
		if (processing->getMessageType() == eMessageType::mtInput)
		{
			shared_ptr<mglInputMessage> inputMessage =  dynamic_pointer_cast<mglInputMessage>(processing);
			processInputMessage(inputMessage);
		}
		else
		{
			/* Search for associated Input type within the message handler map
			 * and execute it. Otherwise we log an ERR and delete the message.
			 */
			mglMessageHandlerMap::iterator findIt = m_mMessageHandlers.find(processing->getMessageType());
			if (findIt != m_mMessageHandlers.end())
			{
				// This will execute the handler
				(*findIt->second)(processing);
			}
			else
			{
				LOG_TRACE("Could not find handler for message type!");
			}
		}
		m_MessageQueue.pop();
	}
}


/**
 * Add a message onto the Queue. This can be every Message we like to process...
 *
 * @param mess The message to add.
 */
void mglSystem::addMessage(shared_ptr<mglMessage> mess)
{
	m_MessageQueue.push(mess);
}


void mglSystem::destroy()
{
	INIT_LOG("mglSystem", "destroy");

	LOG_TRACE("Clearing data sources...");
	map<mglValString, shared_ptr<mglDataSource>>::iterator itDS;
	for (itDS = m_DataSources.begin(); itDS != m_DataSources.end(); itDS++)
		itDS->second->deInit();

	mglLogger::Inst().destroy();
}



shared_ptr<mglGuiObject> mglSystem::getValueEditor()
{
	return m_ValueEditor;
}

shared_ptr<mglGuiObject> mglSystem::getEditedObject()
{
	return m_vSelectionContexts.back()->m_Editing;
}
