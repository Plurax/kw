/*
 * mglTexture.h
 *
 *  Created on: 11.03.2014
 *      Author: cromas
 */

#ifndef MGLTEXTURE_H_
#define MGLTEXTURE_H_

#ifdef WIN32
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#else
#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>
#endif


#include "mglValues/mglValString.h"
#include "mglDebug/mglLogger.h"
#include "FreeImage.h"



/**
 * This is a container for holding textures. The reason to separate this is the possibility that mglSystem
 * init is called before initializing the OpenGL context. For example to get access to the global configuration.
 * This would cause the texture loading to fail. So we separate the init of the textures from their loading into
 * the graphics memory and flag each object with a bool to get information about its init state.
 * This will btw allow dynamic loading of textures anyway...
 */
class mglTexture
{
public:
	mglTexture(mglValString(filename), GLenum image_format, GLint internal_format, GLint level);
	~mglTexture();
	void LoadTexture();
	mglValString m_name; // OK this is held twice - once here in the object, and second as key of the map but anyway we may need both resolutions
	GLuint m_textureId;
	bool m_initialized;

	GLenum m_img_format;
	GLint m_int_format;
	GLint m_level;
};

#endif /* MGLTEXTURE_H_ */
