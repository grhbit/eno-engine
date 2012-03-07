/*
 *  enoConfig.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 12..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */
#pragma once

extern const unsigned int eno_major;
extern const unsigned int eno_minor;
extern const unsigned int revision;

#define ENO_MAJOR eno_major
#define ENO_MINOR eno_minor

#include <iostream>

#if defined (WIN32) | defined (_WIN32) | defined (WIN64) | defined (_WIN64)
#define ENO_WINDOWS_PLATFORM
#define ENO_WINDOWS_DRIVER
#endif

#if defined (__APPLE__) | defined (MACOSX)
#if !defined (MACOSX)
#define MACOSX
#endif
#define ENO_MACOSX_PLATFORM
#define ENO_MACOSX_DRIVER
#endif

#if defined (ENO_WINDOWS_DRIVER)
#define ENO_DISPLAY_DIRECT_9
#define ENO_DISPLAY_DIRECT_10_11
#endif

#define ENO_DISPLAY_OPENGL

#if defined (_MSC_VER)
#define ENO_COMPILED_FROM_VISUAL_STUDIO

#elif defined (__GNUC__)
#define ENO_COMPILED_FROM_GNUC

#elif defined (__TURBOC__) \
|| defined (__BORLANDC__) \
|| defined (__WATCOMC__) \
|| defined (__IBMCPP__)
#error "NOT SUPPORT COMPILER"
#endif

#include "StdString.h"

namespace eno { typedef CStdString CString; }

#if defined (ENO_COMPILED_FROM_VISUAL_STUDIO)
// {
#define ENO_ALIGNED(n) __declspec(align(n))
#include <tchar.h>
#if defined (UNICODE)
#define ENO_UNICODE
typedef wchar_t tchar;
#endif
#define ENO_CLASS_NAME _T("eno")
// }
#elif defined(ENO_COMPILED_FROM_GNUC)
// {
#define ENO_ALIGNED(n) __attribute__ ((aligned(n)))
#define __long_aligned __attribute__((aligned((sizeof(long)))))
#define _T(Str) L##Str
#define ENO_UNICODE
typedef unsigned short tchar;
// }
#endif

#if !defined(ENO_UNICODE)
typedef char tchar;
#endif

#if !defined(interface)
#define interface struct
#endif

#if defined(ENO_COMPILED_FROM_GNUC) && \
	(__GNUC_LIBSTD__ <= 4 && __GNUC_LIBSTD_MINOR__ < 3) || \
	defined(ENO_COMPILED_FROM_VISUAL_STUDIO) && \
	(_MSC_VER < 1600)

const class {
public:
    template <class T>
    operator T*() const
    {
        return 0;
    }
	
    template <class C, class T>
    operator T C::*() const
    {
        return 0;
    }
	
private:
    void operator&() const;
	
} nullptr = {};

#endif

// [skop 8:47 Friday. 8.13. 2010. Created.]
