/*
 *  enoConfig.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 12..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */
#pragma once

extern const unsigned int revision;

#define ENO_MAJOR 0
#define ENO_MINOR 0

// Compiler must be supported C++11 standard.
// Xcode 4.3.2
// Visual Studio 11 Beta

#include <iostream>
#include <regex>
#include <tuple>

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

#elif defined (__llvm__)
#define ENO_COMPILED_FROM_LLVM

#elif defined (__GNUC__)
#define ENO_COMPILED_FROM_GNUC

#elif defined (__TURBOC__) \
|| defined (__BORLANDC__) \
|| defined (__WATCOMC__) \
|| defined (__IBMCPP__)
#error "NOT SUPPORT COMPILER"
#endif

#include "StdString.h"

#ifndef UNUSED
#define UNUSED(x) (void)x
#endif

namespace eno {
    typedef CStdString CString;
    
    // Raw String
    typedef CStdStr<char> RString;
}

#define UNISTRING(X) UTF8(X)
#define UTF8String(X) u8##X
#define UTF8(X) u8##X

#if defined (ENO_COMPILED_FROM_VISUAL_STUDIO)
// {
#define ENO_ALIGNED(n) __declspec(align(n))

#if defined (UNICODE)
#define ENO_UNICODE
#endif
//*/
#define ENO_CLASS_NAME _T("eno")
// }
#elif defined(ENO_COMPILED_FROM_GNUC)
// {
#define ENO_ALIGNED(n) __attribute__ ((aligned(n)))
#define __long_aligned __attribute__((aligned((sizeof(long)))))

#define ENO_UNICODE
// }
#endif

#if !defined(interface)
#define interface class
#endif

#if defined(ENO_COMPILED_FROM_GNUC) && \
	(__GNUC_LIBSTD__ <= 4 && __GNUC_LIBSTD_MINOR__ < 3) || \
	defined(ENO_COMPILED_FROM_VISUAL_STUDIO) && \
	(_MSC_VER < 1600)
/*
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
*/
#endif

// [skop 8:47 Friday. 8.13. 2010. Created.]
