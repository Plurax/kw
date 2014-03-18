
#ifndef H_MGL_WINDOW
#define H_MGL_WINDOW
#include <stdio.h>
#include <vector>
#include <map>
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
#include "mglGui/mglGuiActionFunctor.h"
#include "mglValues/mglValCoord.h"

// Those are bit definitions for special features of several objects:
static const char* enObjectFlagNames[] = { "SELECTABLE", "EDITABLE", "ENTERABLE" };
enum class enObjectFlagsBitNums { Obj_Selectable = 0, Obj_Editable, Obj_Enterable };
enum class enObjectFlags { Obj_Selectable = 1, Obj_Editable = 2, Obj_Enterable = 4};

#define OBJ_SELECTABLE	(unsigned long)0x00000001 // Can be selected with IGR
#define OBJ_EDITABLE	(unsigned long)0x00000002 // Implements editable interface
#define OBJ_ENTERABLE   (unsigned long)0x00000004 // you can step down the tree


#define OBJ_STATE_STANDARD	(unsigned short) 0
#define OBJ_STATE_SELECTED	(unsigned short) 1
#define OBJ_STATE_FOCUSSED	(unsigned short) 2


using namespace xercesc;
using namespace std;


class mglSystem;
class mglGuiObject;

typedef vector<mglGuiObject*> mglGuiObjectList;
typedef map<mglValString, mglGuiObject*> mglGuiObjectMap;

class mglGuiObject
{
public:

	/**
	 * This is the main constructor of the standard gui object class.
	 * It is called from the mglSystem singleton when intitializing the complete GUI from the
	 * xml configuration. The parameter is the treepart of the xml configuration matching the <configuration> tag.
	 * @param xmlconfiguration
	 */
	mglGuiObject(DOMElement* xmlconfiguration);

	mglGuiObject();

	virtual ~mglGuiObject();

	/**
	 * The Draw function is propably the most important function for any GUI object.
	 * Siblings must overwrite this function to implement their own rendering.
	 */
	virtual void Draw();

	float GetWidth();
	void SetWidth(float uiWidth);

	virtual mglGuiObject* getChildAtPosition(mglValCoord pt);
	void setParentWindow(mglGuiObject* parent);
	void setNextWindow(mglGuiObject* parent);
	void setPrevWindow(mglGuiObject* parent);

	// Interface for editables - if not used call the parent function
	virtual void applyIGRCount(int _cnt);
	virtual mglValue* getIncrement(); // This is for touch (slider?) usage
	virtual void setValue(mglValue* _val);

	float GetX();
	float GetY();
	mglValCoord GetPosition();
	void SetPosition(mglValCoord pt);

	float GetHeight();
	void SetHeight(float uiHeight);

	virtual void Connect(mglGuiActionFunctor* func);
	mglMessage* ProcessMessage(mglMessage* message);

	mglGuiActionFunctor* getGuiAction();

	virtual void AddChild(mglGuiObject *Child);
	void RemoveChild(uint ChildID);
	void RemoveChild(mglValString ChildName);
	mglGuiObjectList* getChildren();
	virtual mglGuiObject* getChildByID(unsigned int ID);

	void setState(unsigned short _state);
	unsigned short getState();
	const mglValString& getName();
	void setName(mglValString name);

	mglGuiObject* parent();
	mglGuiObject* prev();
	mglGuiObject* next();

	unsigned long getOptionMask();
	unsigned long getOptionMaskFromString(std::string _str);

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

	mglGuiObjectList m_Children;

	unsigned short m_usState; // focus, selected etc

	bool bVisible;
	bool bHasChildren;

	mglValString m_name;
	mglValColor m_BackGroundColor;
};


#endif
