/*
 * mglBase.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */


#ifndef H_MGL_SYSTEM
#define H_MGL_SYSTEM

#include <stdio.h>
#include <vector>
#include <queue>

#include "mglTimer.h"
#include "mglDebug/mglLogger.h"
#include "mglGui/mglGuiObject.h"
#include "mglGui/mglInputMessage.h"
#include "mglGui/mglDraggingContext.h"
#include "mglGui/mglFontProvider.h"
#include "mglGui/mglGuiLibManager.h"
#include "mglDataLayer/mglDataSourceManager.h"
#include "mglSystem.h"
#include "mglBase.h"
#include "mglMessage.h"
#include "mglAppConfiguration.h"
#include "mglGui/mglSelectionContext.h"

#include "mglValues/mglValString.h"

#include "mglLibHandle.h"

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
#ifdef WIN32
#include <xercesc/util/Transcoders/Win32/Win32TransService.hpp>
#endif
class mglGuiObject;

typedef map<int, shared_ptr<mglMessageHandler>> mglMessageHandlerMap;


using namespace xercesc;
using namespace std;

class mglSystem
{
public:
	void init(void(*ptr)(), mglValString& configfile);

	~mglSystem();

	static mglSystem& Inst()
	{
		/* This is a windows hack to get the mglSystem instance of 
		the main executable accessible within the DLLs
		Linux OS should work out of the box because we load shared libs with global symbols
		available. So the singleton will be unique even in shared object code access.
		*/
#ifdef _USRDLL
		typedef mglSystem* (*GetSystemFn)();
		HMODULE mod = GetModuleHandle(NULL);
		GetSystemFn getSystem = (GetSystemFn)::GetProcAddress(mod, "GetSystem");
		mglSystem* _instance = getSystem();
		return *_instance;
#else
		static mglSystem _instance;
		return _instance;
#endif
	}

	void Draw(void);
	void SetMainFrame(shared_ptr<mglGuiObject> MainFrame);

	void closeMenu();
	void returnFromMenu();
	void openMenu(shared_ptr<mglGuiObject>Menu, mglValCoord _coord);

	void destroy();
	shared_ptr<mglGuiObject> getMainFrame(mglValString name);
	shared_ptr<mglGuiObject> getMenu(mglValString name);

	shared_ptr<mglGuiObject> getValueEditor();
	shared_ptr<mglGuiObject> getEditedObject();

	shared_ptr<mglMessage> processInputMessage(shared_ptr<mglInputMessage> Message);

	void readConfiguration(mglValString& configFile);
	void (*flushGL)();
	shared_ptr<mglGuiObject> getTargetWindow(mglValCoord pt);

	shared_ptr<mglGuiObject> getGuiObject(mglValString _str);

	mglGuiObjectMap m_mMainFrames;
	mglGuiObjectMap m_mMenus;
	mglGuiObjectMap m_mEditors;

	mglMessageHandlerMap m_mMessageHandlers;

	mglGuiObjectMap m_mGuiObjects;

	mglDataSourceMap m_DataSources;

	shared_ptr<mglDataSource> getDataSource(mglValString _name);

	shared_ptr<mglFontProvider> m_FontProvider;
	shared_ptr<mglTextureManager> m_TextureManager;

	mglAppConfiguration m_Configuration;

	mglLibraryInfo* m_libInfo;

	void processEvents();
	void addMessage(shared_ptr<mglMessage> mess);

	void setMessageHandlers(DOMNode* _currentElement);
	void loadMessageHandler(DOMNode* _currentElement);


	// On windows we force to use UTF8 - so we need to create a seperate Transcoder!
#ifdef WIN32
	XMLTranscoder* UTF8_TRANSCODER = NULL;
#endif
private:
	int m_pixelformat;

	mglSystem();
	xercesc::XercesDOMParser *m_ConfigFileParser;
    XMLCh* m_TAG_root;
    void createGUIfromXML(DOMNode* currentElement, shared_ptr<mglGuiObject> parent, shared_ptr<mglGuiObject> prev, mglGuiObjectMap& listToAdd, int _listtype);
    void createDataLayer(DOMNode* currentElement);

    XMLCh* m_TAG_ApplicationSettings;

	bool m_dbf;

	bool m_ButtonDown; // is mouse or IGR button down?

	// This is for managing state changes when flipping between touch and IGR input
	bool m_lastActionCausedByTouch;

	shared_ptr<mglDraggingContext> m_DraggingContext;

	shared_ptr<mglGuiObject> m_CurrentMainFrame;
	shared_ptr<mglGuiObject> m_CurrentMenu;

	vector<shared_ptr<mglSelectionContext>> m_vSelectionContexts;

	mglTimer m_ContextMenuTimer;
	shared_ptr<mglGuiObject> m_ContextAnimation;

	shared_ptr<mglGuiObject> m_ValueEditor;

	queue<shared_ptr<mglMessage>> m_MessageQueue;
};



#endif
