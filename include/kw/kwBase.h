/*
 * kwBase.h
 *
 *  Created on: 12.10.2013
 *      Author: chuhlich
 */
#ifndef H_KW_BASE
#define H_KW_BASE

#ifdef WIN32
#include <Windows.h>
#endif

#if defined(KW_STATIC_LIB)
	#define KW_DLL_API
	#define KW_DLL_CALLCONV
#else
	#if defined(_WIN32) || defined(__WIN32__)
		#define KW_DLL_CALLCONV __stdcall
		// The following ifdef block is the standard way of creating macros which make exporting 
		// from a DLL simpler. All files within this DLL are compiled with the KW_EXPORTS
		// symbol defined on the command line. this symbol should not be defined on any project
		// that uses this DLL. This way any other project whose source files include this file see 
		// DLL_API functions as being imported from a DLL, wheras this DLL sees symbols
		// defined with this macro as being exported.
		#ifdef KW_EXPORTS
			#define KW_DLL_API __declspec(dllexport)
		#else
			#define KW_DLL_API __declspec(dllimport)
		#endif // KW_EXPORTS
	#else 
		// try the gcc visibility support (see http://gcc.gnu.org/wiki/Visibility)
		#if defined(__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
			#ifndef GCC_HASCLASSVISIBILITY
				#define GCC_HASCLASSVISIBILITY
			#endif
		#endif // __GNUC__
		#define KW_DLL_CALLCONV
		#if defined(GCC_HASCLASSVISIBILITY)
			#define KW_DLL_API __attribute__ ((visibility("default")))
		#else
			#define KW_DLL_API
		#endif		
	#endif // WIN32 / !WIN32
#endif // KW_STATIC_LIB


#ifndef __LIBNAME
#define __LIBNAME "undefinedLib"
#endif

#include "kwObject.h"
#include "kwSystem.h"
#include "kwTimer.h"




#endif
