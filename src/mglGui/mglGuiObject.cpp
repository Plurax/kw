

#include "mglGui/mglGuiObject.h"
#include "mglDebug/mglLogger.h"
#include <memory>

#include <stdio.h>
#include <string>

using namespace std;


mglGuiObject::mglGuiObject()
{}

mglGuiObject::mglGuiObject(json configuration)
{
	int x,y;

	m_ulOptionMask = 0;

	m_EditorName = mglValString();

	x = configuration["xpos"].get<float>();
	y = configuration["ypos"].get<float>();

	m_fWidth = configuration["width"].get<float>();
	m_fHeight = configuration["height"].get<float>();

	std::string xstr = configuration["backgroundcolor"];
	m_BackGroundColor = mglValColor(xstr.c_str());

	if (configuration.count("optionflags"))
	{
		xstr = (configuration["optionflags"]).get<string>();
		m_ulOptionMask = mglGuiObject::getOptionMaskFromString(xstr);
	}
	else
		m_ulOptionMask = 0;

	m_GuiAction = nullptr; // on creation there is no function defined!
	m_Position = mglValCoord(x, y, 0);
	m_bVisible = true;
	m_bHasChildren = false;
}


mglGuiObject::~mglGuiObject()
{
}


void mglGuiObject::Connect(shared_ptr<mglMessageHandler> func)
{
	m_GuiAction = func;
}

shared_ptr<mglMessage> mglGuiObject::ProcessMessage(shared_ptr<mglMessage> message)
{
	return (*m_GuiAction)(message);
}

shared_ptr<mglMessageHandler> mglGuiObject::getGuiAction()
{
	return m_GuiAction;
}


/**
 * Returns the X coordinate of the position of this object. Relative positioning is not regarded.
 * @return
 */
float mglGuiObject::GetX()
{
	return m_Position.m_fX;
}


/**
 * Returns the Y coordinate of the position of this object. Relative positioning is not regarded.
 * @return
 */
float mglGuiObject::GetY()
{
	return m_Position.m_fY;
}


/**
 * Returns the height of the object.
 * @return
 */
float mglGuiObject::GetHeight()
{
	return m_fHeight;
}

/**
 * This method returns the position which is set for this object. Relative positioning is not regarded.
 * @return
 */
mglValCoord mglGuiObject::GetPosition()
{
	return m_Position;
}


/**
 * In contrast to the getposition method, this method returns the position coordinate with regard to relative positioning.
 * That means if the current object is positioned relatively this function will step up to the parents until it gets the first
 * absolute position. All positions are added and the result is returned.
 * @return
 */
mglValCoord mglGuiObject::calcPosition()
{
	INIT_LOG("mglGuiObject", "calcPosition");
	if (m_ulOptionMask & static_cast<unsigned long>(enumObjectFlags::Obj_PositionRelative))
	{
		mglValCoord cParent = m_pParent->calcPosition();
		mglValCoord ret = mglValCoord(cParent.m_fX + m_Position.m_fX, cParent.m_fY - m_Position.m_fY, cParent.m_fZ + m_Position.m_fZ);;

		return ret;
	}
	else
		return m_Position;
}


void mglGuiObject::SetPosition(mglValCoord pt)
{
	m_Position = pt;
}


float mglGuiObject::GetWidth()
{
	return m_fWidth;
}


void mglGuiObject::SetWidth(float fWidth)
{
	m_fWidth = fWidth;
}

void mglGuiObject::Draw(void)
{
	mglValCoord calcPos = calcPosition();

	// the position coordinates always point to the top left!
	glColor4f(m_BackGroundColor.fRed,m_BackGroundColor.fGreen,m_BackGroundColor.fBlue,m_BackGroundColor.fAlpha);

	glBegin (GL_QUADS);

	glVertex2f(calcPos.m_fX, calcPos.m_fY); // Unten links der Textur und des Quadrats
	glVertex2f(calcPos.m_fX + m_fWidth, calcPos.m_fY); // Unten rechts der Textur und des Quadrats
	glVertex2f(calcPos.m_fX + m_fWidth, calcPos.m_fY - m_fHeight); // Oben rechts der Textur und des Quadrats
	glVertex2f(calcPos.m_fX, calcPos.m_fY - m_fHeight);
	glEnd ();

	// assure painting of all children
	for (unsigned int i = 0; i < m_Children.size(); ++i)
		m_Children.at(i)->Draw();
}

void mglGuiObject::AddChild(shared_ptr<mglGuiObject> Child)
{
//	INIT_LOG("mglGuiObject", "AddChild(mglWindow *Child)");
//	LOG_TRACE("Added child");

	if (m_bHasChildren)
	{
		m_Children.back()->setNextWindow(Child);
		Child->setPrevWindow(m_Children.back());
	}
	else
		m_bHasChildren = true;

	Child->setParentWindow(shared_from_this());

	m_Children.push_back(Child);
}

void mglGuiObject::initChildren()
{
}

mglGuiObjectList* mglGuiObject::getChildren()
{
	return &m_Children;
}


void mglGuiObject::setState(unsigned short _state)
{
	m_usState = _state;
}

unsigned short mglGuiObject::getState()
{
	return m_usState;
}

void mglGuiObject::setParentWindow(shared_ptr<mglGuiObject> parent)
{
	m_pParent = parent;
}

void mglGuiObject::setEditor(shared_ptr<mglValString> _editor)
{
	m_EditorName = mglValString(*_editor);
}


shared_ptr<mglGuiObject> mglGuiObject::parent()
{
	return m_pParent;
}

shared_ptr<mglGuiObject> mglGuiObject::prev()
{
	return m_pPrev;
}

shared_ptr<mglGuiObject> mglGuiObject::next()
{
	return m_pNext;
}

unsigned long mglGuiObject::getOptionMask()
{
	return m_ulOptionMask;
}

void mglGuiObject::setOptionMask(unsigned long _mask)
{
	m_ulOptionMask = _mask;
}


void mglGuiObject::setNextWindow(shared_ptr<mglGuiObject> parent)
{
	m_pNext = parent;
}

const mglValString& mglGuiObject::getName()
{
	return m_name;
}

void mglGuiObject::setName(mglValString name)
{
	m_name = name;
}

void mglGuiObject::setPrevWindow(shared_ptr<mglGuiObject> parent)
{
	m_pPrev = parent;
}


shared_ptr<mglGuiObject> mglGuiObject::getChildAtPosition(mglValCoord pt)
{
	const mglGuiObjectList::const_iterator it_end = m_Children.end();
	
	if (!m_bHasChildren)
		return shared_from_this();
	mglValCoord coord;
	mglGuiObjectList::const_iterator child;
	for (child = m_Children.begin(); child != it_end; ++child)
	{
		if ((*child)->isVisible())
		{
			coord = (*child)->calcPosition();

			if ((pt.m_fX >= coord.m_fX) &&
				(pt.m_fX < (coord.m_fX + (*child)->GetWidth())) &&
				(pt.m_fY <= coord.m_fY) &&
				(pt.m_fY > (coord.m_fY - (*child)->GetHeight())))
			{
				if ((*child)->hasChildren())
				{
					shared_ptr<mglGuiObject> const window = (*child)->getChildAtPosition(pt);
					if (window)
						return window;
					else
						return nullptr;

				}
				else
					return *child;
			}
		}
	}
	return nullptr;
}

shared_ptr<mglGuiObject> mglGuiObject::getChildByID(unsigned int ID)
{
	if (m_bHasChildren)
	{
		if (m_Children.size() > ID)
			return m_Children.at(ID);
	}
	return NULL;
}

/**
 * If the editable flag is set the system will try to apply IGR counts on the object
 * This function handles them
 * @param _cnt
 */
void mglGuiObject::applyIGRCount(int _cnt)
{

}

/**
 * If the editable flag is set the system will try to apply modifications via external objects
 * in case of touch modification (sliders etc)
 * @return
 */
shared_ptr<mglValue> mglGuiObject::getIncrement() // This is for touch (slider?) usage
{
	return NULL; // this is the base class
}

/**
 * Hard set the value - this function is separate because the value to be set
 * is defined by the implementation of the object.
 * @param _val
 */
void mglGuiObject::setValue(shared_ptr<mglValue> _val)
{

}

/**
 * Get the value - this function is separate because the value to be set
 * is defined by the implementation of the object.
 * @param _val
 */
shared_ptr<mglValue> mglGuiObject::getValue()
{
	return NULL;
}

void mglGuiObject::InitEditable(shared_ptr<mglGuiObject> edited)
{

}

/*@
 * This will return NULL to get the system use the editor named by the valtype of the
 * hold value of the object.
 */
mglValString mglGuiObject::getEditorName()
{
	return m_EditorName;
}

shared_ptr<mglValue> mglGuiObject::getUpperLimit()
{
	return NULL;
}

shared_ptr<mglValue> mglGuiObject::getLowerLimit()
{
	return NULL;
}


float mglGuiObject::getMinDragX()
{
	return 0.0;
}

float mglGuiObject::getMaxDragX()
{
	return 0.0;
}

float mglGuiObject::getMinDragY()
{
	return 0.0;
}

float mglGuiObject::getMaxDragY()
{
	return 0.0;
}

/**
 * This function derives the optionmask via the enumeration names out of a string.
 * The user can specify the optionmask via their names in the XML instead of using a difficult understandable number.
 * @param _str
 */
unsigned long mglGuiObject::getOptionMaskFromString(std::string _str)
{
	INIT_LOG("mglGuiObject", "getOptionMaskFromString(std::string _str)");
//	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
	unsigned long retVal = 0;

	std::stringstream ss(_str);
	std::string item;
	while (std::getline(ss, item, ',')) {
//		LOG_TRACE("line: " << item);
		if (item.empty())
			continue;
		if (0 == item.compare(string(enumObjectFlagNames[static_cast<unsigned long>(enumObjectFlagsBitNums::Obj_Selectable)])))
			retVal |= (1 << static_cast<int>(enumObjectFlagsBitNums::Obj_Selectable));
		if (0 == item.compare(string(enumObjectFlagNames[static_cast<unsigned long>(enumObjectFlagsBitNums::Obj_Editable)])))
			retVal |= (1 << static_cast<int>(enumObjectFlagsBitNums::Obj_Editable));
		if (0 == item.compare(string(enumObjectFlagNames[static_cast<unsigned long>(enumObjectFlagsBitNums::Obj_Enterable)])))
			retVal |= (1 << static_cast<int>(enumObjectFlagsBitNums::Obj_Enterable));
		if (0 == item.compare(string(enumObjectFlagNames[static_cast<unsigned long>(enumObjectFlagsBitNums::Obj_PositionRelative)])))
			retVal |= (1 << static_cast<int>(enumObjectFlagsBitNums::Obj_PositionRelative));
		if (0 == item.compare(string(enumObjectFlagNames[static_cast<unsigned long>(enumObjectFlagsBitNums::Obj_DraggableX)])))
			retVal |= (1 << static_cast<int>(enumObjectFlagsBitNums::Obj_DraggableX));
		if (0 == item.compare(string(enumObjectFlagNames[static_cast<unsigned long>(enumObjectFlagsBitNums::Obj_DraggableY)])))
			retVal |= (1 << static_cast<int>(enumObjectFlagsBitNums::Obj_DraggableY));
	}
//	LOG_TRACE("retval = " << retVal);
	return retVal;
}

