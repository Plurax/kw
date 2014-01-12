

#include "../include/mglGuiObject.h"
#include "mglLogger.h"

#include <stdio.h>

using namespace std;

mglGuiObject::mglGuiObject()
{
	m_GuiAction = NULL; // on creation there is no function defined!
}

mglGuiObject::mglGuiObject(DOMElement* xmlconfiguration)
{

	DOMNodeList*      children = xmlconfiguration->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_xpos = XMLString::transcode("xpos");
	XMLCh* TAG_ypos = XMLString::transcode("ypos");
	XMLCh* TAG_width = XMLString::transcode("width");
	XMLCh* TAG_height = XMLString::transcode("height");

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
		}
	}
	m_GuiAction = NULL; // on creation there is no function defined!
	iXpos = x;
	iYpos = y;
	iHeight = height;
	iWidth = width;
	bVisible = true;
	bHasChildren = false;
}


mglGuiObject::mglGuiObject(int X, int Y, int W, int H)
{
	m_GuiAction = NULL; // on creation there is no function defined!
	iXpos = X;
	iYpos = Y;
	iHeight = H;
	iWidth = W;
	bVisible = true;
	bHasChildren = false;
}


mglGuiObject::~mglGuiObject()
{
	for (size_t i = 0; i < Children.size(); ++i)
		delete Children.at(i);
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

int mglGuiObject::GetX()
{
	return iXpos;
}


int mglGuiObject::GetY()
{
	return iYpos;
}

int mglGuiObject::GetHeight()
{
	return iHeight;
}


int mglGuiObject::GetWidth()
{
	return iWidth;
}

void mglGuiObject::Draw(void)
{
	// the position coordinates always point to the top left!
	glColor3f(1.0f,1.0f,1.0f);

	glBegin (GL_QUADS);


	glVertex2i(iXpos, iYpos); // Unten links der Textur und des Quadrats  
	glVertex2i(iXpos + iWidth, iYpos); // Unten rechts der Textur und des Quadrats  
	glVertex2i(iXpos + iWidth, iYpos - iHeight); // Oben rechts der Textur und des Quadrats  
	glVertex2i(iXpos, iYpos - iHeight);
	glEnd ();

	// assure painting of all children
	for (size_t i = 0; i < Children.size(); ++i)
		Children.at(i)->Draw();
}

void mglGuiObject::AddChild(mglGuiObject *Child)
{
	INIT_LOG("AddChild(mglWindow *Child");
	LOG_TRACE("Added child");

	if (bHasChildren)
	{
		Children.back()->setNextWindow(Child);
		Child->setPrevWindow(Children.back());
	}
	else
		bHasChildren = true;

	Children.push_back(Child);
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

void mglGuiObject::setNextWindow(mglGuiObject* parent)
{
	m_pNext = parent;
}

void mglGuiObject::setPrevWindow(mglGuiObject* parent)
{
	m_pPrev = parent;
}


mglGuiObject* mglGuiObject::getChildAtPosition(mglCoord pt)
{
	const WindowList::const_iterator it_end = Children.end();
	
	if (!bHasChildren)
		return this;

	WindowList::const_iterator child;
	for (child = Children.begin(); child != it_end; ++child)
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
	if ((bHasChildren) && (Children.size() > ID))
	{
		return Children.at(ID);
	}
	return 0;
}
