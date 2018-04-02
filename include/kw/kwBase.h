/*
 * kwBase.h
 *
 *  Created on: 12.10.2013
 *      Author: chuhlich
 */
#ifndef H_KW_BASE
#define H_KW_BASE

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


#ifndef __LIBNAME
#define __LIBNAME "undefinedLib"
#endif

#include "kw/kwObject.h"
#include "kw/kwSystem.h"
#include "kw/kwTimer.h"




#endif
