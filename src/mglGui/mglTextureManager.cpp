//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#include "mglGui/mglTextureManager.h"
#include "mglDebug/mglLogger.h"

#include <GL/glx.h>    /* this includes the necessary X headers */
#include <GL/gl.h>


mglTextureManager::mglTextureManager()
{
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_Initialise();
	#endif
}

//these should never be called
//TextureManager::TextureManager(const TextureManager& tm){}
//TextureManager& TextureManager::operator=(const TextureManager& tm){}
	
mglTextureManager::~mglTextureManager()
{
	// call this ONLY when linking with FreeImage as a static library
	#ifdef FREEIMAGE_LIB
		FreeImage_DeInitialise();
	#endif

	UnloadAllTextures();
}

bool mglTextureManager::LoadTexture(const char* filename, GLenum image_format, GLint internal_format, GLint level, GLint border)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	FIBITMAP* bitmap = FreeImage_Load(format, filename);

	FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
	int nWidth = FreeImage_GetWidth(pImage);
	int nHeight = FreeImage_GetHeight(pImage);

	std::cout << "w : " << nWidth << " H: " << nHeight<< "\n";

	GLubyte* textura = new GLubyte[4*nWidth*nHeight];
	char* pixeles = (char*)FreeImage_GetBits(pImage);
	if (!pixeles)
		std::cout << "ERROR no pixels\n";
	else
		std::cout << "pixels\n";

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, nWidth, nHeight, 0, GL_RGBA,GL_UNSIGNED_BYTE,(GLvoid*)textura );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	GLenum huboError = glGetError();
	if(huboError){

		std::cout<<"There was an error loading the texture"<<endl;
	}

	delete textura;
	FreeImage_Unload(bitmap);
	FreeImage_Unload(pImage);

	m_mTextures.insert(std::pair<mglValString,GLuint>(mglValString(filename),gl_texID));

	return true;
}

bool mglTextureManager::UnloadTexture(mglValString texFile)
{
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the map
	if(m_mTextures.find(texFile) != m_mTextures.end())
	{
		glDeleteTextures(1, &(m_mTextures[texFile]));
		m_mTextures.erase(texFile);
	}
	//otherwise, unload failed
	else
	{
		result = false;
	}

	return result;
}

bool mglTextureManager::BindTexture(mglValString texFile)
{
	bool result(true);
	std::map<mglValString, GLuint>::iterator texIt;
	texIt = m_mTextures.find(texFile);
	texIt = m_mTextures.begin();

	//if this texture ID mapped, bind it's texture as current
	if(texIt != m_mTextures.end())
		glBindTexture(GL_TEXTURE_2D, texIt->second);
	//otherwise, binding failed
	else
		result = false;

	return result;
}

void mglTextureManager::UnloadAllTextures()
{
	//start at the begginning of the texture map
	std::map<mglValString, GLuint>::iterator i = m_mTextures.begin();

	//Unload the textures untill the end of the texture map is found
	while(i != m_mTextures.end())
		UnloadTexture(i->first);

	//clear the texture map
	m_mTextures.clear();
}
