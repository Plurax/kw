//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#include "mglGui/mglTextureManager.h"
#include "mglGui/mglTexture.h"
#include "mglDebug/mglLogger.h"



mglTextureManager::mglTextureManager()
{
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif
}

	
mglTextureManager::~mglTextureManager()
{
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif

	UnloadAllTextures();
}

/**
 * Texture manager uses a two step mechanism for managing textures.
 * First the textures are registered into a map by their filename.
 * Then the first call to the bind function will cause the initialization of the texture by loading the
 * file and generating the texture data into the graphics memory.
 * This will allow us to call the init function of mglSystem before having a running OpenGL context.
 * @param filename
 * @param image_format
 * @param internal_format
 * @param level
 */
void mglTextureManager::RegisterTexture(const char* filename, GLenum image_format, GLint internal_format, GLint level)
{
	mglTexture* newTex = new mglTexture(mglValString(filename), image_format, internal_format, level);
	std::pair<std::map<mglValString, mglTexture*>::iterator, bool> retIt;
	retIt = m_mTextures.insert(std::pair<mglValString,mglTexture*>(mglValString(filename),newTex));
	if (!retIt.second)
	{
		INIT_LOG("mglTextureManager", "RegisterTexture(const char* filename, GLenum image_format, GLint internal_format, GLint level)");
		THROW_TECHNICAL_EXCEPTION(67, "Error while registering texture " << filename << " : this filename is already in the map.");
	}
}

/**
 * This will unload a specifig texture identified by its filename.
 * Use this with care - the texture is cleared from graphics memory and removed from the map!
 * @param texFile
 * @return
 */
bool mglTextureManager::UnloadTexture(mglValString texFile)
{
	bool result(true);
	std::map<mglValString, mglTexture*>::iterator mapIt;
	mapIt = m_mTextures.find(texFile);
	//if this texture ID mapped, unload it's texture, and remove it from the map
	if(mapIt != m_mTextures.end())
	{
		delete mapIt->second;
		m_mTextures.erase(mapIt); // remove the entry from the map
	}
	//otherwise, unload failed
	else
	{
		result = false;
	}

	return result;
}


/**
 * Bind a texture via its gl texture id. Used for rendering.
 * @param texFile: The file name of the texture being bound
 * @return
 */
bool mglTextureManager::BindTexture(mglValString texFile)
{
	bool result(true);
	std::map<mglValString, mglTexture*>::iterator texIt;
	texIt = m_mTextures.find(texFile);
	texIt = m_mTextures.begin();

	//if this texture ID mapped, bind it's texture as current
	if(texIt != m_mTextures.end())
	{
		if (!texIt->second->m_initialized)
			texIt->second->LoadTexture();
		glBindTexture(GL_TEXTURE_2D, texIt->second->m_textureId);
	}
	//otherwise, binding failed
	else
		result = false;

	return result;
}

/**
 * This will call the destructor for each texture object in the map.
 * The map is cleared after deleting all objects.
 */
void mglTextureManager::UnloadAllTextures()
{
	//start at the begginning of the texture map
	std::map<mglValString, mglTexture*>::iterator i = m_mTextures.begin();

	//Unload the textures untill the end of the texture map is found
	for (i = m_mTextures.begin(); i != m_mTextures.end(); i++)
	{
		delete i->second;
	}

	//clear the texture map
	m_mTextures.clear();
}




/**
 * Creates the datalayer configured below the given element.
 * After creation of the object each one is initialized.
 * @param _currentElement
 */
void mglTextureManager::initTextures(DOMNode* _currentElement)
{
	INIT_LOG("mglTextureManager", "initTextures(DOMNode* _currentElement)");

	DOMElement* currentElement = dynamic_cast< xercesc::DOMElement* >(_currentElement);

	DOMNodeList*      children = currentElement->getChildNodes();
	const  XMLSize_t nodeCount = children->getLength();

	XMLCh* TAG_Texture = XMLString::transcode("Texture");

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
			if ( XMLString::equals(currentElement->getTagName(), TAG_Texture))
			{
				std::string filename = XMLString::transcode(currentElement->getTextContent());
				RegisterTexture(filename.c_str(), GL_RGBA, GL_RGB, 0);

				LOG_TRACE("Got texture named: " << filename.c_str());

			}
		}
	}

	XMLString::release(&TAG_Texture);

}
