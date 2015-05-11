/*
 * mglTexture.cpp
 *
 *  Created on: 11.03.2014
 *      Author: cromas
 */




#include "mglGui/mglTexture.h"
#include "mglDebug/mglDebug.h"


mglTexture::mglTexture(mglValString name, GLenum image_format, GLint internal_format, GLint level)
{
	m_initialized = false;
	m_name = name;
	m_img_format = image_format;
	m_int_format = internal_format;
	m_level = level;
	m_textureId = 0;
}


mglTexture::~mglTexture()
{
	glDeleteTextures(1, &m_textureId);
}

void mglTexture::LoadTexture()
{
	INIT_LOG("mglTexture", "LoadTexture()");
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(m_name.str()->c_str(), 0);
	FIBITMAP* bitmap = FreeImage_Load(format, m_name.str()->c_str());

	FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	GLubyte* textura = new GLubyte[4*nWidth*nHeight];
	char* pixeles = (char*)FreeImage_GetBits(pImage);
	if (!pixeles)
	{
		std::cout << "ERROR no pixels\n";
		THROW_TECHNICAL_EXCEPTION(456, "Could not get Pixels from freeimage while loading texture");
	}

	//FreeImage loads in BGR format, so you need to swap some bytes(Or use GL_BGR).
	for(int j= 0; j < (nWidth * nHeight); j++){
		textura[j*4+0]= pixeles[j*4+2];
		textura[j*4+1]= pixeles[j*4+1];
		textura[j*4+2]= pixeles[j*4+0];
		textura[j*4+3]= pixeles[j*4+3];
	}

	GLuint gl_texID;
    glGenTextures(1, &gl_texID);

	glBindTexture(GL_TEXTURE_2D, gl_texID);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, nWidth, nHeight, 0, GL_RGBA,GL_UNSIGNED_BYTE,(GLvoid*)textura );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLenum huboError = glGetError();
	if(huboError)
	{
		std::cout<<"There was an error loading the texture"<<endl;
		THROW_TECHNICAL_EXCEPTION(457, "GL Error while loading texture");
	}

	delete textura;
	FreeImage_Unload(bitmap);
	FreeImage_Unload(pImage);

	m_textureId = gl_texID;
	m_initialized = true;
}


