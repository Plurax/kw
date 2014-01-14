
#include <vector>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdexcept>


#include "../include/mglSystem.h"

using namespace xercesc;
using namespace std;


void mglSystem::init(GLXContext context, Display *disp, Window win, GLboolean dblbuff)
{
	// Insert default factory into the list
	mglGuiLibManager& objManager = mglGuiLibManager::Inst();
	objManager.init();

	/* Prepare XML Parser */
   try
   {
	   XMLPlatformUtils::Initialize();  // Initialize Xerces infrastructure
   }
   catch( XMLException& e )
   {
      char* message = XMLString::transcode( e.getMessage() );
      cerr << "XML toolkit initialization error: " << message << endl;
      XMLString::release( &message );
      // throw exception here to return ERROR_XERCES_INIT
   }

   // Tags and attributes used in XML file.
   // Can't call transcode till after Xerces Initialize()
   m_ConfigFileParser = new XercesDOMParser;

	std::string configfile("Configuration.xml");
	readConfiguration(configfile);

	/* Create graphics context... */
	//InitGraphics(context);
	sCurrentMainFrame = 0;
	m_display = disp;
	m_window = win;
	m_dbf = dblbuff;

}

mglSystem::~mglSystem()
{
	uint uiIndex;
	for (uiIndex = 0; uiIndex < m_MainFrames.size(); uiIndex++)
		delete m_MainFrames.at(uiIndex); // delete the root frame objects
	m_MainFrames.clear(); // clear all registered root frames
	m_FontProvider->Delete(); // delete the singleton
}

mglMessage* mglSystem::sendInputMessage(mglInputMessage* Message)
{
	// find the target object
	mglGuiObject *Target = getTargetWindow(Message->getCoord());
	if (Target != NULL)
		if (Target->getGuiAction() != NULL)
		{
			Message->setTarget(Target);
			return Target->ProcessMessage(Message);
		}
	return NULL;
}



void mglSystem::Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// render all the currently active main frame
	m_MainFrames.at(sCurrentMainFrame)->Draw();

    // Show the new scene
	if (m_dbf)
		glXSwapBuffers(m_display, m_window);/* buffer swap does implicit glFlush */
	else
		glFlush();  /* explicit flush for single buffered case */

}


mglGuiObject* mglSystem::getTargetWindow(mglCoord pt)
{
	mglGuiObject* destination;
	destination = m_CurrentMainFrame; // set target to current root mainframe

	if (!destination->isVisible())
		return 0;

	// then search within the concatenation for the final input target
	if ((pt.getX() >= m_CurrentMainFrame->GetX()) &&
		(pt.getX() < (m_CurrentMainFrame->GetX() + m_CurrentMainFrame->GetWidth())) &&
		(pt.getY() >= m_CurrentMainFrame->GetY()) &&
		(pt.getY() < (m_CurrentMainFrame->GetY() + m_CurrentMainFrame->GetHeight())))
	{
		destination = m_CurrentMainFrame->getChildAtPosition(pt); 
		return destination;
	}
	return 0;
}

mglGuiObject* mglSystem::getMainFrameByID(unsigned int ID)
{
	if (ID < m_MainFrames.size())
		return m_MainFrames.at(ID);
	else
		return 0;
}


void mglSystem::SetMainFrame(mglGuiObject *MainFrame)
{
	m_CurrentMainFrame = MainFrame;
}

/*
 * Reads the complete configuration file and creates the corresponding graphic objects via
 * loading of shared libs and factory pattern.
 */
void mglSystem::readConfiguration(std::string& configFile)
{
	// Test to see if the file is ok.
   struct stat fileStatus;

   errno = 0;
   if(stat(configFile.c_str(), &fileStatus) == -1) // ==0 ok; ==-1 error
   {
       if( errno == ENOENT )      // errno declared by include file errno.h
          throw ( std::runtime_error("Path file_name does not exist, or path is an empty string.") );
       else if( errno == ENOTDIR )
          throw ( std::runtime_error("A component of the path is not a directory."));
       else if( errno == ELOOP )
          throw ( std::runtime_error("Too many symbolic links encountered while traversing the path."));
       else if( errno == EACCES )
          throw ( std::runtime_error("Permission denied."));
       else if( errno == ENAMETOOLONG )
          throw ( std::runtime_error("File can not be read\n"));
   }

   m_ConfigFileParser->setValidationScheme( XercesDOMParser::Val_Never );
   m_ConfigFileParser->setDoNamespaces( false );
   m_ConfigFileParser->setDoSchema( false );
   m_ConfigFileParser->setLoadExternalDTD( false );

   XMLCh* TAG_GUI = XMLString::transcode("GUI");
   XMLCh* TAG_AppConfiguration = XMLString::transcode("AppConfiguration");
   XMLCh* TAG_Logging = XMLString::transcode("Logging");
   try
   {
      m_ConfigFileParser->parse( configFile.c_str() );

      // no need to free this pointer - owned by the parent parser object
      DOMDocument* xmlDoc = m_ConfigFileParser->getDocument();

      // Get the top-level element: NAme is "root". No attributes for "root"

      DOMElement* elementRoot = xmlDoc->getDocumentElement();
      if( !elementRoot )
    	  throw(std::runtime_error( "empty XML document" ));
	  // Parse XML file for tags of interest: "ApplicationSettings"
      // Look one level nested within "root". (child of root)

		DOMNodeList*      children = elementRoot->getChildNodes();
		const  XMLSize_t nodeCount = children->getLength();

		// For all nodes, children of "root" in the XML tree.

		for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
		{
			DOMNode* currentNode = children->item(xx);
			if( currentNode->getNodeType() &&  // true is not NULL
					currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
			{
				// Found node which is an Element. Re-cast node as element
				DOMElement* currentElement
							= dynamic_cast< xercesc::DOMElement* >( currentNode );

				if ( XMLString::equals(currentElement->getTagName(), TAG_Logging))
				{
					mglLogger::Inst().configure(currentNode);
				}
				if ( XMLString::equals(currentElement->getTagName(), TAG_AppConfiguration))
				{
				   // Already tested node as type element and of name "ApplicationSettings".
				  // Read attributes of element "ApplicationSettings".
				}

				if ( XMLString::equals(currentElement->getTagName(), TAG_GUI))
				{
					createGUIfromXML(currentNode, NULL, NULL);
				}
			}
	  }
   }
   catch( xercesc::XMLException& e )
   {
      char* message = xercesc::XMLString::transcode( e.getMessage() );
      ostringstream errBuf;
      errBuf << "Error parsing file: " << message << flush;
      XMLString::release( &message );
   }
}

// This is recursive creation of the GUI Tree
void mglSystem::createGUIfromXML(DOMNode* GUIELement, mglGuiObject* parent, mglGuiObject* prev)
{
	INIT_LOG("mglSystem", "createGUIfromXML(DOMNode* GUIELement, mglGuiObject* parent, mglGuiObject* prev)");

	DOMNode* currentNode = GUIELement;
	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >(GUIELement);

	DOMNodeList*      children = GUIELement->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	mglGuiObject* thisWindow = NULL;
	mglGuiObject* prevWindow = NULL;

	XMLCh* TAG_mglWindowItem = XMLString::transcode("mglWindowItem");

	// For all nodes, children of "GUI" in the XML tree.
	for( XMLSize_t xx = 0; xx < nodeCount; ++xx )
	{
		DOMNode* currentNode = children->item(xx);
		if( currentNode->getNodeType() &&  // true is not NULL
				currentNode->getNodeType() == DOMNode::ELEMENT_NODE ) // is element
		{
			// Found node which is an Element. Re-cast node as element
			DOMElement* currentElement
						= dynamic_cast< xercesc::DOMElement* >( currentNode );
			if ( XMLString::equals(currentElement->getTagName(), TAG_mglWindowItem))
			{
				/* The XML should always contain the following four tags at this point:
				 * <name>,<libname>, <classname> and <configuration>
				 * The programmer can even replace the frame object implementation by using
				 * his own library at this point!
				 */

				DOMElement* DE_name = currentElement->getFirstElementChild();
				DOMElement* DE_libname = DE_name->getNextElementSibling();
				DOMElement* DE_classname = DE_libname->getNextElementSibling();

				DOMElement* DE_func_libname = DE_classname->getNextElementSibling();
				DOMElement* DE_func_classname = DE_func_libname->getNextElementSibling();

				DOMElement* DE_configuration = DE_func_classname->getNextElementSibling();
				DOMElement* DE_children = DE_configuration->getNextElementSibling();

				/*
				 * Name is mandatory
				 */
				LOG_TRACE("Got GUI Element named: " << XMLString::transcode(DE_name->getTextContent()));

				// Create the configured element via the factory

				string* name = new string(XMLString::transcode(DE_name->getTextContent()));
				string* libname = new string(XMLString::transcode(DE_libname->getTextContent()));
				string* classname = new string(XMLString::transcode(DE_classname->getTextContent()));

				thisWindow = mglGuiLibManager::Inst().createGUIObject(libname,
													classname,
													DE_configuration);

				libname = new string(XMLString::transcode(DE_func_libname->getTextContent()));
				classname = new string(XMLString::transcode(DE_func_classname->getTextContent()));

				mglGuiActionFunctor* funct = mglGuiLibManager::Inst().createGuiAction(libname, classname);
				thisWindow->Connect(funct);
				// After we created the object we can attach the handler if it exists

				// We are at parent level - so this is a main frame
				if (parent == NULL)
					m_MainFrames.push_back(thisWindow);
				else
				{
					thisWindow->setParentWindow(parent);
					parent->AddChild(thisWindow);
				}

				// Now ascend down and create the children
				if (DE_children->getChildNodes()->getLength() > 0)
				{
					createGUIfromXML(DE_children, thisWindow, NULL);
				}
				prevWindow = thisWindow;
			}
		}
  }

}


void mglSystem::destroy()
{
	mglLogger::Inst().destroy();
}

