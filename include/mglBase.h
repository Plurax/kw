/*
 * mglBase.h
 *
 *  Created on: 12.10.2013
 *      Author: cromas
 */
#ifndef H_MGL_BASE
#define H_MGL_BASE

#ifdef WIN32
#include <Windows.h>
#endif

#if defined(MGL_STATIC_LIB)
	#define MGL_DLL_API
	#define MGL_DLL_CALLCONV
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#define MGL_DLL_CALLCONV __stdcall
		// The following ifdef block is the standard way of creating macros which make exporting 
		// from a DLL simpler. All files within this DLL are compiled with the MGL_EXPORTS
		// symbol defined on the command line. this symbol should not be defined on any project
		// that uses this DLL. This way any other project whose source files include this file see 
		// DLL_API functions as being imported from a DLL, wheras this DLL sees symbols
		// defined with this macro as being exported.
		#ifdef MGL_EXPORTS
			#define MGL_DLL_API __declspec(dllexport)
		#else
			#define MGL_DLL_API __declspec(dllimport)
		#endif // MGL_EXPORTS
	#else 
		// try the gcc visibility support (see http://gcc.gnu.org/wiki/Visibility)
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#ifndef GCC_HASCLASSVISIBILITY
				#define GCC_HASCLASSVISIBILITY
			#endif
		#endif // __GNUC__
		#define MGL_DLL_CALLCONV
		#if defined(GCC_HASCLASSVISIBILITY)
			#define MGL_DLL_API __attribute__ ((visibility("default")))
		#else
			#define MGL_DLL_API
		#endif		
	#endif // WIN32 / !WIN32
#endif // MGL_STATIC_LIB


#ifndef __LIBNAME
#define __LIBNAME "undefinedLib"
#endif

#include "mglGui/mglGuiObject.h"
#include "mglGui/mglFontProvider.h"
#include "mglGui/mglTextureManager.h"
#include "mglSystem.h"
#include "mglTimer.h"
#include "FTGL/ftgl.h"




#endif
