
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
#include "mglGuiActionFunctor.h"
#include "mglCoord.h"

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

	void SetPosition(mglCoord pt);

	int GetWidth();
	void SetWidth(uint uiWidth);

	virtual mglGuiObject* getChildAtPosition(mglCoord pt);
	void setParentWindow(mglGuiObject* parent);
	void setNextWindow(mglGuiObject* parent);
	void setPrevWindow(mglGuiObject* parent);

	int GetX();
	int GetY();
	mglCoord GetPosition();

	int GetHeight();
	void SetHeight(uint uiHeight);

	virtual void Connect(mglGuiActionFunctor* func);
	mglMessage* ProcessMessage(mglMessage* message);

	mglGuiActionFunctor* getGuiAction();

	virtual void AddChild(mglGuiObject *Child);
	void RemoveChild(uint ChildID);
	void RemoveChild(std::string ChildName);
	void setState(unsigned short _state);
	unsigned short getState();


	virtual mglGuiObject* getChildByID(unsigned int ID);

	virtual bool hasChildren() {return bHasChildren; };
	virtual bool isVisible() { return bVisible;};
protected:
	uint uiElementState; // State of element, inactive, focussed, selected

	mglGuiActionFunctor* m_GuiAction;

	int iXpos;
	int iYpos;
	int iHeight;
	int iWidth;

	mglGuiObject* m_pParent;
	mglGuiObject* m_pPrev;
	mglGuiObject* m_pNext;

	WindowList Children;

	unsigned short m_usState; // focus, selected etc

	bool bVisible;
	bool bHasChildren;

	std::string m_name;
};


#endif
