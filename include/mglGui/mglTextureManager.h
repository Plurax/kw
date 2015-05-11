/*
 * mglTextureManager.h
 *
 *  Created on: 21.03.2014
 *      Author: cromas
 */

//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#ifndef H_MGL_TEXTUREMANAGER
#define H_MGL_TEXTUREMANAGER
#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#endif

#define TEXMANAGER  TextureManager::Inst()

#include "FreeImage.h"
#include <map>

#include "mglGui/mglTexture.h"
#include "mglDebug/mglDebug.h"

#include "mglValues/mglValString.h"



#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMDocumentType.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMText.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>


using namespace xercesc;

class mglTextureManager
{
public:

	mglTextureManager();
	~mglTextureManager();
	void initTextures(DOMNode* _currentElement);

	//load a texture an make it the current texture
	//if texID is already in use, it will be unloaded and replaced with this texture
	void RegisterTexture(const char* filename,	//where to load the file from
		GLenum image_format = GL_RGB,		//format the image is in
		GLint internal_format = GL_RGB,		//format to store the image in
		GLint level = 0);					//mipmapping level
//		GLint border = 0);					//border size

	//free the memory for a texture
	bool UnloadTexture(mglValString texFile);

	//set the current texture
	bool BindTexture(mglValString texFile);

	//free all texture memory
	void UnloadAllTextures();

protected:
	std::map<mglValString, mglTexture*> m_mTextures;
};

#endif
