
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
static const char* enumObjectFlagNames[] = { "SELECTABLE", "EDITABLE", "ENTERABLE", "POSITIONRELATIVE", "DRAGGABLEX", "DRAGGABLEY", "FIXEDEDITOR" };
enum class enumObjectFlagsBitNums {
	Obj_Selectable = 0, /** Object can be selected - this will cause input processing (touch) and focus selection (IGR) for this object if occurs */
	Obj_Editable, /** The object is editable, that means it contains a modifiable value. When selected an edit object is spawned (touch)
					or this object will receive further inputs (IGR). */
	Obj_Enterable, /** This object can be used as grouping layer for IGR inputs. Selecting will cause stepping down the selection list to its children. */
	Obj_PositionRelative, /** Should be clear */
	Obj_DraggableX,
	Obj_DraggableY,
	Obj_FixedEditor // This editor is not positioned at opening, it has always the same position as configured
};
enum class enumObjectFlags {
	Obj_Selectable = 1,
	Obj_Editable = 2,
	Obj_Enterable = 4,
	Obj_PositionRelative = 8,
	Obj_DraggableX = 16,
	Obj_DraggableY = 32,
	Obj_FixedEditor = 64
};



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
	void SetWidth(float fWidth);

	virtual mglGuiObject* getChildAtPosition(mglValCoord pt);
	void setParentWindow(mglGuiObject* parent);
	void setNextWindow(mglGuiObject* parent);
	void setPrevWindow(mglGuiObject* parent);

	// Interface for editables - if not used call the parent function (and nothing happens)
	virtual void applyIGRCount(int _cnt);
	virtual mglValue* getIncrement(); // This is for touch (slider?) usage
	virtual mglValue* getUpperLimit();
	virtual mglValue* getLowerLimit();
	virtual void setValue(mglValue* _val);
	virtual mglValue* getValue();
	virtual void InitEditable(mglGuiObject* edited);
	mglValString getEditorName(); // This will return of the editor which is desired to be used for this objects value

	// Those functions are for draggable objects to avoid move out of their limits
	virtual float getMinDragX();
	virtual float getMaxDragX();
	virtual float getMinDragY();
	virtual float getMaxDragY();

	float GetX();
	float GetY();
	mglValCoord GetPosition();
	void SetPosition(mglValCoord pt);
	mglValCoord calcPosition();

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
	void setOptionMask(unsigned long _mask);
	unsigned long getOptionMaskFromString(std::string _str);

	virtual bool hasChildren() {return m_bHasChildren; };
	virtual bool isVisible() { return m_bVisible;};

protected:
	uint uiElementState; // State of element, inactive, focussed, selected
	unsigned long m_ulOptionMask;

	mglGuiActionFunctor* m_GuiAction;

	mglValCoord m_Position;

	float m_fHeight;
	float m_fWidth;

	mglGuiObject* m_pParent;
	mglGuiObject* m_pPrev;
	mglGuiObject* m_pNext;

	mglGuiObjectList m_Children;

	unsigned short m_usState; // focus, selected etc

	bool m_bVisible;
	bool m_bHasChildren;

	mglValString m_name;
	mglValString m_EditorName;
	mglValColor m_BackGroundColor;
};


#endif
