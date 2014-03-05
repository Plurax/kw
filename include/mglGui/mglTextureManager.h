//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#ifndef H_MGL_TEXTUREMANAGER
#define H_MGL_TEXTUREMANAGER

#define TEXMANAGER  TextureManager::Inst()


#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#include "FreeImage.h"
#include <map>

#include "mglValues/mglValString.h"

class mglTextureManager
{
public:

	mglTextureManager();
	~mglTextureManager();

	//load a texture an make it the current texture
	//if texID is already in use, it will be unloaded and replaced with this texture
	bool LoadTexture(const char* filename,	//where to load the file from
		GLenum image_format = GL_RGB,		//format the image is in
		GLint internal_format = GL_RGB,		//format to store the image in
		GLint level = 0,					//mipmapping level
		GLint border = 0);					//border size

	//free the memory for a texture
	bool UnloadTexture(mglValString texFile);

	//set the current texture
	bool BindTexture(mglValString texFile);

	//free all texture memory
	void UnloadAllTextures();

protected:
	std::map<mglValString, GLuint> m_mTextures;
};

#endif
