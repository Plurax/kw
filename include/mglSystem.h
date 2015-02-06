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
#include "mglSelectionContext.h"

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

class mglGuiObject;

using namespace xercesc;

class mglSystem
{
public:
	void init(void (*_flushGL)());
	~mglSystem();

	static mglSystem& Inst()
	{
		static mglSystem _instance;
		return _instance;
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

	mglGuiObjectMap m_mGuiObjects;

	mglDataSourceMap m_DataSources;

	mglDataSource* getDataSource(mglValString _name);

	mglFontProvider* m_FontProvider;
	mglTextureManager* m_TextureManager;

	mglAppConfiguration m_Configuration;

	mglLibraryInfo* m_libInfo;

	void processEvents();
	void addMessage(mglMessage* mess);

private:
	int m_pixelformat;

	mglSystem();
	xercesc::XercesDOMParser *m_ConfigFileParser;
    XMLCh* m_TAG_root;
    void createGUIfromXML(DOMNode* currentElement, mglGuiObject* parent, mglGuiObject* prev, mglGuiObjectMap& listToAdd, int _listtype);
    void createDataLayer(DOMNode* currentElement);

    XMLCh* m_TAG_ApplicationSettings;

	Display *m_display;
	Window m_window;
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
