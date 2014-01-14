

#ifndef H_MGL_SYSTEM
#define H_MGL_SYSTEM

#include <stdio.h>
#include <vector>


#include "Logger/mglLogger.h"
#include "mglGuiObject.h"
#include "mglInputMessage.h"

#include "../include/mglFontProvider.h"
#include "../include/mglGuiLibManager.h"
#include "../include/mglSystem.h"
#include "../include/mglBase.h"
#include "../include/mglMessage.h"


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
	void init(GLXContext context, Display *disp, Window win, GLboolean dblbuff);
	~mglSystem();

	static mglSystem& Inst()
	{
		static mglSystem _instance;
		return _instance;
	}

	void Draw(void);
	void SetMainFrame(mglGuiObject *MainFrame);
	void destroy();
	mglGuiObject* getMainFrameByID(unsigned int ID);

	mglMessage* sendInputMessage(mglInputMessage* Message);

	void readConfiguration(std::string& configFile);

	mglGuiObject* getTargetWindow(mglCoord pt);

	WindowList m_MainFrames;
	mglFontProvider *m_FontProvider;

private:
	int m_pixelformat;

	xercesc::XercesDOMParser *m_ConfigFileParser;
    XMLCh* m_TAG_root;
    void createGUIfromXML(DOMNode* currentElement, mglGuiObject* parent, mglGuiObject* prev);

    XMLCh* m_TAG_ApplicationSettings;

	Display *m_display;
	Window m_window;
	bool m_dbf;

	int m_ScreenXRes;
	int m_ScreenYRes;
	mglGuiObject *m_CurrentMainFrame;
	mglGuiObject *m_CurrentMenu; // This can also be every mglWindow - but it is shown via zbuffering before the mainframe

	mglGuiObject *m_CurrentFocus; /* This pointer contains the object which holds focus in time - this is modified by
									prev/next concatenation of focussable objects by the nextfocus/prevfocus events (ie. IGR increment/decrement)
									*/
	short sCurrentMainFrame; // defines which one is currently shown
};

#endif
