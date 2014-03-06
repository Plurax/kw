

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

	int x,y,width,height;

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
		}
	}
	m_GuiAction = NULL; // on creation there is no function defined!
	m_fXpos = x;
	m_fYpos = y;
	m_fHeight = height;
	m_fWidth = width;
	bVisible = true;
	bHasChildren = false;
	m_ulOptionMask = getOptionMaskFromString(string(""));
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

float mglGuiObject::GetX()
{
	return m_fXpos;
}


float mglGuiObject::GetY()
{
	return m_fYpos;
}

float mglGuiObject::GetHeight()
{
	return m_fHeight;
}


float mglGuiObject::GetWidth()
{
	return m_fWidth;
}

void mglGuiObject::Draw(void)
{
	// the position coordinates always point to the top left!
	glColor3f(m_BackGroundColor.fRed,m_BackGroundColor.fGreen,m_BackGroundColor.fBlue);

	glBegin (GL_QUADS);

	glVertex2f(m_fXpos, m_fYpos); // Unten links der Textur und des Quadrats
	glVertex2f(m_fXpos + m_fWidth, m_fYpos); // Unten rechts der Textur und des Quadrats
	glVertex2f(m_fXpos + m_fWidth, m_fYpos - m_fHeight); // Oben rechts der Textur und des Quadrats
	glVertex2f(m_fXpos, m_fYpos - m_fHeight);
	glEnd ();

	// assure painting of all children
	for (size_t i = 0; i < m_Children.size(); ++i)
		m_Children.at(i)->Draw();
}

void mglGuiObject::AddChild(mglGuiObject *Child)
{
	INIT_LOG("mglGuiObject", "AddChild(mglWindow *Child");
	LOG_TRACE("Added child");

	if (bHasChildren)
	{
		m_Children.back()->setNextWindow(Child);
		Child->setPrevWindow(m_Children.back());
	}
	else
		bHasChildren = true;

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
	
	if (!bHasChildren)
		return this;

	mglGuiObjectList::const_iterator child;
	for (child = m_Children.begin(); child != it_end; ++child)
	{
		if ((*child)->isVisible())
		{
			if ((pt.getX() >= (*child)->GetX()) &&
				(pt.getX() < ((*child)->GetX() + (*child)->GetWidth())) &&
				(pt.getY() <= (*child)->GetY()) &&
				(pt.getY() > ((*child)->GetY() - (*child)->GetHeight())))
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
	if ((bHasChildren) && (m_Children.size() > ID))
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
 * is definde by the implementation of the object.
 * @param _val
 */
void mglGuiObject::setValue(mglValue* _val)
{

}


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
		if (0 == item.compare(string(enObjectFlagNames[static_cast<int>(enObjectFlagsBitNums::Obj_Selectable)])))
			retVal |= (1 << static_cast<int>(enObjectFlagsBitNums::Obj_Selectable));
		if (0 == item.compare(string(enObjectFlagNames[static_cast<int>(enObjectFlagsBitNums::Obj_Editable)])))
			retVal |= (1 << static_cast<int>(enObjectFlagsBitNums::Obj_Editable));
		if (0 == item.compare(string(enObjectFlagNames[static_cast<int>(enObjectFlagsBitNums::Obj_Enterable)])))
			retVal |= (1 << static_cast<int>(enObjectFlagsBitNums::Obj_Enterable));
		LOG_TRACE("Accesstest: " << string(enObjectFlagNames[static_cast<int>(enObjectFlagsBitNums::Obj_Selectable)]));
		LOG_TRACE("Accesstest: " << string(enObjectFlagNames[static_cast<int>(enObjectFlagsBitNums::Obj_Editable)]));
		LOG_TRACE("Accesstest: " << string(enObjectFlagNames[static_cast<int>(enObjectFlagsBitNums::Obj_Enterable)]));
	}
	LOG_TRACE("retval = " << retVal);
	return retVal;
}
