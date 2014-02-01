

#ifndef H_MGL_SYSTEM
#define H_MGL_SYSTEM

#include <stdio.h>
#include <vector>


#include "mglLogger/mglLogger.h"
#include "mglGui/mglGuiObject.h"
#include "mglGui/mglInputMessage.h"

#include "mglGui/mglFontProvider.h"
#include "mglGui/mglGuiLibManager.h"
#include "mglDataLayer/mglDataSourceManager.h"
#include "mglSystem.h"
#include "mglBase.h"
#include "mglMessage.h"
#include "mglAppConfiguration.h"


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
	void init(GLXContext context, void (*_flushGL)());
	~mglSystem();

	static mglSystem& Inst()
	{
		static mglSystem _instance;
		return _instance;
	}

	void Draw(void);
	void SetMainFrame(mglGuiObject *MainFrame);
	void SetMenu(mglGuiObject *Menu);
	void destroy();
	mglGuiObject* getMainFrameByID(unsigned int ID);
	mglGuiObject* getMenuByID(unsigned int ID);

	mglMessage* sendInputMessage(mglInputMessage* Message);

	void readConfiguration(std::string& configFile);
	void (*flushGL)();
	mglGuiObject* getTargetWindow(mglValCoord pt);

	mglWindowList m_MainFrames;
	mglWindowList m_Menus;

	mglDataSourceMap m_DataSources;

	mglFontProvider *m_FontProvider;

	mglAppConfiguration m_Configuration;

private:
	int m_pixelformat;

	xercesc::XercesDOMParser *m_ConfigFileParser;
    XMLCh* m_TAG_root;
    void createGUIfromXML(DOMNode* currentElement, mglGuiObject* parent, mglGuiObject* prev, mglWindowList& listToAdd);
    void createDataLayer(DOMNode* currentElement);

    XMLCh* m_TAG_ApplicationSettings;

	Display *m_display;
	Window m_window;
	bool m_dbf;

	int m_ScreenXRes;
	int m_ScreenYRes;

	mglGuiObject *m_CurrentMainFrame;
	mglGuiObject *m_SelectListParent;
	mglGuiObject *m_CurrentMenu; // This can also be every mglWindow - but it is shown via zbuffering before the mainframe

	mglWindowList* m_pCurrentSelectionList;
	mglGuiObject *m_CurrentFocus; /* This pointer contains the object which holds focus in time - this is modified by
									prev/next concatenation of focussable objects by the nextfocus/prevfocus events (ie. IGR increment/decrement)
									*/
	short m_sCurrentMainFrame; // defines which one is currently shown
	short m_sCurrentMenu; // defines which menu is currently shown
};

#endif
