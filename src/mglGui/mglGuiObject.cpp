

#include "mglGui/mglGuiObject.h"
#include "mglDebug/mglLogger.h"

#include <stdio.h>
#include <string>

using namespace std;


mglGuiObject::mglGuiObject()
{}

mglGuiObject::mglGuiObject(DOMElement* xmlconfiguration)
{

	DOMNodeList*      children = xmlconfiguration->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_xpos = XMLString::transcode("xpos");
	XMLCh* TAG_ypos = XMLString::transcode("ypos");
	XMLCh* TAG_width = XMLString::transcode("width");
	XMLCh* TAG_height = XMLString::transcode("height");
	XMLCh* TAG_backgroundcolor = XMLString::transcode("backgroundcolor");
	XMLCh* TAG_optionflags= XMLString::transcode("optionflags");

	int x,y,width,height;

	m_ulOptionMask = 0;

	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
			if ( XMLString::equals(currentElement->getTagName(), TAG_xpos))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				x = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_ypos))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				y = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_width))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				width = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_height))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				height = atoi(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_backgroundcolor))
			{
				std::string xstr = XMLString::transcode(currentElement->getTextContent());
				m_BackGroundColor = mglValColor(xstr.c_str());
			}

			if ( XMLString::equals(currentElement->getTagName(), TAG_optionflags))
			{
				char* optionflags = XMLString::transcode(currentElement->getTextContent());
				m_ulOptionMask = mglGuiObject::getOptionMaskFromString(string(optionflags));
			}
		}
	}


	XMLString::release(&TAG_xpos);
	XMLString::release(&TAG_ypos);
	XMLString::release(&TAG_width);
	XMLString::release(&TAG_height);
	XMLString::release(&TAG_backgroundcolor);
	XMLString::release(&TAG_optionflags);

	m_GuiAction = NULL; // on creation there is no function defined!
	m_Position = mglValCoord(x, y, 0);
	m_fHeight = height;
	m_fWidth = width;
	m_bVisible = true;
	m_bHasChildren = false;
}


mglGuiObject::~mglGuiObject()
{
	for (size_t i = 0; i < m_Children.size(); ++i)
		delete m_Children.at(i);
}


void mglGuiObject::Connect(mglGuiActionFunctor* func)
{
	m_GuiAction = func;
}

mglMessage* mglGuiObject::ProcessMessage(mglMessage* message)
{
	return (*m_GuiAction)(message);
}

mglGuiActionFunctor* mglGuiObject::getGuiAction()
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
	for (size_t i = 0; i < m_Children.size(); ++i)
		m_Children.at(i)->Draw();
}

void mglGuiObject::AddChild(mglGuiObject *Child)
{
	INIT_LOG("mglGuiObject", "AddChild(mglWindow *Child)");
	LOG_TRACE("Added child");

	if (m_bHasChildren)
	{
		m_Children.back()->setNextWindow(Child);
		Child->setPrevWindow(m_Children.back());
	}
	else
		m_bHasChildren = true;

	Child->setParentWindow(this);

	m_Children.push_back(Child);
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

void mglGuiObject::setParentWindow(mglGuiObject* parent)
{
	m_pParent = parent;
}

mglGuiObject* mglGuiObject::parent()
{
	return m_pParent;
}

mglGuiObject* mglGuiObject::prev()
{
	return m_pPrev;
}

mglGuiObject* mglGuiObject::next()
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


void mglGuiObject::setNextWindow(mglGuiObject* parent)
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

void mglGuiObject::setPrevWindow(mglGuiObject* parent)
{
	m_pPrev = parent;
}


mglGuiObject* mglGuiObject::getChildAtPosition(mglValCoord pt)
{
	const mglGuiObjectList::const_iterator it_end = m_Children.end();
	
	if (!m_bHasChildren)
		return this;
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
					mglGuiObject* const window = (*child)->getChildAtPosition(pt);
					if (window)
						return window;
					else
						return 0;

				}
				else
					return *child;
			}
		}
	}
	return 0;
}

mglGuiObject* mglGuiObject::getChildByID(unsigned int ID)
{
	if ((m_bHasChildren) && (m_Children.size() > ID))
	{
		return m_Children.at(ID);
	}
	return 0;
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
mglValue* mglGuiObject::getIncrement() // This is for touch (slider?) usage
{

}

/**
 * Hard set the value - this function is separate because the value to be set
 * is defined by the implementation of the object.
 * @param _val
 */
void mglGuiObject::setValue(mglValue* _val)
{

}

/**
 * Get the value - this function is separate because the value to be set
 * is defined by the implementation of the object.
 * @param _val
 */
mglValue* mglGuiObject::getValue()
{

}

void mglGuiObject::InitEditable(mglGuiObject* edited)
{

}


mglValue* mglGuiObject::getUpperLimit()
{

}

mglValue* mglGuiObject::getLowerLimit()
{

}


float mglGuiObject::getMinDragX()
{

}

float mglGuiObject::getMaxDragX()
{

}

float mglGuiObject::getMinDragY()
{

}

float mglGuiObject::getMaxDragY()
{

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
		LOG_TRACE("line: " << item);
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
	LOG_TRACE("retval = " << retVal);
	return retVal;
}

