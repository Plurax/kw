/*
 * mglGuiObject.h
 *
 *  Created on: 21.03.2014
 *      Author: cromas
 */


#ifndef H_MGL_GUIOBJECT
#define H_MGL_GUIOBJECT
#include <stdio.h>
#include <vector>
#include <map>
#include <string>


#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#endif

#include <mglMessageHandler.h>
#include <json.hpp>

#include "mglMessage.h"
#include "mglValues/mglValColor.h"
#include "mglValues/mglValCoord.h"


using namespace std;

// Those are bit definitions for special features of several objects:
static const char* enumObjectFlagNames[] = { "SELECTABLE", "EDITABLE", "ENTERABLE", "POSITIONRELATIVE", "DRAGGABLEX", "DRAGGABLEY", "FIXEDEDITOR" };
enum class enumObjectFlagsBitNums {
/** Object can be selected - this will cause input processing (touch) 
	and focus selection (IGR) for this object if occurs */
	Obj_Selectable = 0, 
/** The object is editable, that means it contains a modifiable value. When selected an edit object is spawned (touch)
	or this object will receive further inputs (IGR). */
	Obj_Editable, 
/** This object can be used as grouping layer for IGR inputs. 
	Selecting will cause stepping down the selection list to its children. */
	Obj_Enterable, 
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


using namespace std;
using json = nlohmann::json;

class mglSystem;
class mglGuiObject;

typedef vector<shared_ptr<mglGuiObject>> mglGuiObjectList;
typedef map<mglValString, shared_ptr<mglGuiObject>> mglGuiObjectMap;

class mglGuiObject : public std::enable_shared_from_this<mglGuiObject>
{
public:

	/**
	 * This is the main constructor of the standard gui object class.
	 * It is called from the mglSystem singleton when intitializing the complete GUI from the
	 * xml configuration. The parameter is the treepart of the xml configuration matching the <configuration> tag.
	 * @param xmlconfiguration
	 */
	mglGuiObject(json configuration);

	mglGuiObject();

	virtual ~mglGuiObject();

	/**
	 * The Draw function is propably the most important function for any GUI object.
	 * Siblings must overwrite this function to implement their own rendering.
	 */
	virtual void Draw();

	float GetWidth();
	void SetWidth(float fWidth);

	virtual shared_ptr<mglGuiObject> getChildAtPosition(mglValCoord pt);
	void setParentWindow(shared_ptr<mglGuiObject> parent);
	void setNextWindow(shared_ptr<mglGuiObject> parent);
	void setPrevWindow(shared_ptr<mglGuiObject> parent);
	void setEditor(shared_ptr<mglValString> _editor);

	// Interface for editables - if not used call the parent function (and nothing happens)
	virtual void applyIGRCount(int _cnt);
	virtual shared_ptr<mglValue> getIncrement(); // This is for touch (slider?) usage
	virtual shared_ptr<mglValue> getUpperLimit();
	virtual shared_ptr<mglValue> getLowerLimit();
	virtual void setValue(shared_ptr<mglValue> _val);
	virtual shared_ptr<mglValue> getValue();
	virtual void InitEditable(shared_ptr<mglGuiObject> edited);
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

	void Connect(shared_ptr<mglMessageHandler> func);

	shared_ptr<mglMessage> ProcessMessage(shared_ptr<mglMessage> message);

	shared_ptr<mglMessageHandler> getGuiAction();

	virtual void AddChild(shared_ptr<mglGuiObject> Child);
	virtual void initChildren();
	void RemoveChild(unsigned int ChildID);
	void RemoveChild(mglValString ChildName);
	mglGuiObjectList* getChildren();
	virtual shared_ptr<mglGuiObject> getChildByID(unsigned int ID);

	void setState(unsigned short _state);
	unsigned short getState();
	const mglValString& getName();
	void setName(mglValString name);

	shared_ptr<mglGuiObject> parent();
	shared_ptr<mglGuiObject> prev();
	shared_ptr<mglGuiObject> next();

	unsigned long getOptionMask();
	void setOptionMask(unsigned long _mask);
	unsigned long getOptionMaskFromString(std::string _str);

	virtual bool hasChildren() {return m_bHasChildren; };
	virtual bool isVisible() { return m_bVisible;};

protected:
	unsigned int uiElementState; // State of element, inactive, focussed, selected
	unsigned long m_ulOptionMask;

	shared_ptr<mglMessageHandler> m_GuiAction;
	std::function<shared_ptr<mglMessageHandler>(shared_ptr<mglMessageHandler>)> m_GuiAction_fct;

	mglValCoord m_Position;

	float m_fHeight;
	float m_fWidth;

	shared_ptr<mglGuiObject> m_pParent;
	shared_ptr<mglGuiObject> m_pPrev;
	shared_ptr<mglGuiObject> m_pNext;

	mglGuiObjectList m_Children;

	unsigned short m_usState; // focus, selected etc

	bool m_bVisible;
	bool m_bHasChildren;

	mglValString m_name;
	mglValString m_EditorName;
	mglValColor m_BackGroundColor;
};


#endif
