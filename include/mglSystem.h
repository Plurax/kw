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
#include <xercesc/util/Transcoders/Win32/Win32TransService.hpp>

class mglGuiObject;

typedef map<int, mglMessageHandler*> mglMessageHandlerMap;


using namespace xercesc;

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
	void SetMainFrame(mglGuiObject *MainFrame);

	void closeMenu();
	void returnFromMenu();
	void openMenu(mglGuiObject *Menu, mglValCoord _coord);

	void destroy();
	mglGuiObject* getMainFrame(mglValString name);
	mglGuiObject* getMenu(mglValString name);

	mglGuiObject* getValueEditor();
	mglGuiObject* getEditedObject();

	mglMessage* processInputMessage(mglInputMessage* Message);

	void readConfiguration(mglValString& configFile);
	void (*flushGL)();
	mglGuiObject* getTargetWindow(mglValCoord pt);

	mglGuiObject* getGuiObject(mglValString _str);

	mglGuiObjectMap m_mMainFrames;
	mglGuiObjectMap m_mMenus;
	mglGuiObjectMap m_mEditors;

	mglMessageHandlerMap m_mMessageHandlers;

	mglGuiObjectMap m_mGuiObjects;

	mglDataSourceMap m_DataSources;

	mglDataSource* getDataSource(mglValString _name);

	mglFontProvider* m_FontProvider;
	mglTextureManager* m_TextureManager;

	mglAppConfiguration m_Configuration;

	mglLibraryInfo* m_libInfo;

	void processEvents();
	void addMessage(mglMessage* mess);

	void setMessageHandlers(DOMNode* _currentElement);
	void loadMessageHandler(DOMNode* _currentElement);


	// On windows we force to use UTF8 - so we need to create a seperate Transcoder!
	XMLTranscoder* UTF8_TRANSCODER = NULL;
private:
	int m_pixelformat;

	mglSystem();
	xercesc::XercesDOMParser *m_ConfigFileParser;
    XMLCh* m_TAG_root;
    void createGUIfromXML(DOMNode* currentElement, mglGuiObject* parent, mglGuiObject* prev, mglGuiObjectMap& listToAdd, int _listtype);
    void createDataLayer(DOMNode* currentElement);

    XMLCh* m_TAG_ApplicationSettings;

	bool m_dbf;

	bool m_ButtonDown; // is mouse or IGR button down?

	// This is for managing state changes when flipping between touch and IGR input
	bool m_lastActionCausedByTouch;

	mglDraggingContext* m_DraggingContext;

	mglGuiObject* m_CurrentMainFrame;
	mglGuiObject* m_CurrentMenu;

	vector<mglSelectionContext*> m_vSelectionContexts;

	mglTimer m_ContextMenuTimer;
	mglGuiObject* m_ContextAnimation;

	mglGuiObject* m_ValueEditor;

	std::queue<mglMessage*> m_MessageQueue;
};



#endif
