
#ifndef H_MGL_WINDOW
#define H_MGL_WINDOW
#include <stdio.h>
#include <vector>
#include <string>


#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include "mglMessage.h"
#include "mglValues/mglValColor.h"
#include "mglGuiActionFunctor.h"
#include "mglValues/mglValCoord.h"

// Those are bit definitions for special features of several objects:
#define OBJ_IGR_SELECTABLE	(unsigned long)0x00000001
#define OBJ_IGR_EDITABLE	(unsigned long)0x00000002


#define OBJ_STATE_STANDARD	(unsigned short) 0
#define OBJ_STATE_SELECTED	(unsigned short) 1
#define OBJ_STATE_FOCUSSED	(unsigned short) 2


using namespace xercesc;


class mglSystem;
class mglGuiObject;

typedef std::vector<mglGuiObject*> WindowList;

class mglGuiObject
{
public:

	mglGuiObject();
	mglGuiObject(int X, int Y, int W, int H);

	mglGuiObject(DOMElement* xmlconfiguration);

	mglGuiObject(mglGuiObject *psParent, uint X, uint Y, uint W, uint H);

	virtual ~mglGuiObject();

	virtual void Draw();

	void SetPosition(mglValCoord pt);

	float GetWidth();
	void SetWidth(float uiWidth);

	virtual mglGuiObject* getChildAtPosition(mglValCoord pt);
	void setParentWindow(mglGuiObject* parent);
	void setNextWindow(mglGuiObject* parent);
	void setPrevWindow(mglGuiObject* parent);

	float GetX();
	float GetY();
	mglValCoord GetPosition();

	float GetHeight();
	void SetHeight(float uiHeight);

	virtual void Connect(mglGuiActionFunctor* func);
	mglMessage* ProcessMessage(mglMessage* message);

	mglGuiActionFunctor* getGuiAction();

	virtual void AddChild(mglGuiObject *Child);
	void RemoveChild(uint ChildID);
	void RemoveChild(std::string ChildName);
	WindowList* getChildren();
	virtual mglGuiObject* getChildByID(unsigned int ID);

	void setState(unsigned short _state);
	unsigned short getState();
	const std::string& getName();
	void setName(std::string name);

	mglGuiObject* parent();
	mglGuiObject* prev();
	mglGuiObject* next();

	unsigned long getOptionMask();

	virtual bool hasChildren() {return bHasChildren; };
	virtual bool isVisible() { return bVisible;};
protected:
	uint uiElementState; // State of element, inactive, focussed, selected
	unsigned long m_ulOptionMask;

	mglGuiActionFunctor* m_GuiAction;

	float m_fXpos;
	float m_fYpos;
	float m_fHeight;
	float m_fWidth;

	mglGuiObject* m_pParent;
	mglGuiObject* m_pPrev;
	mglGuiObject* m_pNext;

	WindowList m_Children;

	unsigned short m_usState; // focus, selected etc

	bool bVisible;
	bool bHasChildren;

	std::string m_name;
	mglValColor m_BackGroundColor;
};


#endif