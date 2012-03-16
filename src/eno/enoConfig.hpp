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

namespace eno {
    typedef CStdString CString;
    
    // Raw String
    typedef CStdStr<char> RString;
}

#if defined (ENO_COMPILED_FROM_VISUAL_STUDIO)
// {
#define ENO_ALIGNED(n) __declspec(align(n))
//*/
namespace eno {

class UTF8String
{
    char* utf8string;
    
public:
    UTF8String(const wchar_t* unicodedata) : utf8string(0)
    {
        size_t size = wcslen(unicodedata);

        size_t count = 0;
        for (size_t i = 0; i < size; i++)
        {
            if (unicodedata[i] < 0x80)
                count += 1;
            else if (unicodedata[i] < 0x800)
                count += 2;
            else if (unicodedata[i] < 0x10000)
                count += 3;
        }

        utf8string = new char[count];
        count = 0;

        for (size_t i = 0; i < size; i++)
        {
            if (unicodedata[i] < 0x80)
                utf8string[count++] = unicodedata[i];
            else if (unicodedata[i] < 0x800)
            {
                utf8string[count++] = (unicodedata[i]&0x07C0)>>0x6 | 0x0C0;
                utf8string[count++] = (unicodedata[i]&0x003F)      | 0x080;
            }
            else if (unicodedata[i] < 0x10000)
            {
                utf8string[count++] = (unicodedata[i]&0xF000)>>0xC | 0x0E0;
                utf8string[count++] = (unicodedata[i]&0x0FC0)>>0x6 | 0x080;
                utf8string[count++] = (unicodedata[i]&0x003F)      | 0x080;
            }
        }       
        
    }
    
    ~UTF8String(void)
    {
        if (utf8string != 0)
            delete utf8string;
    }
    
    operator RString () { return utf8string; }
    
    operator char* () { return utf8string; }
    
    operator const char* const () { return utf8string; }
    
    operator const RString const () { return utf8string; }
};

}
 
#define UNISTRING(X) UTF8(X)
#define UTF8(X) UTF8String(L##X)

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
//*/

namespace eno {
/*
class UTF8String 
{
public:
    UTF8String(const wchar_t* unicodedata) : utf8string(0)
    {
        size_t size = wcslen(unicodedata);
        
        utf8string = new char[size];
        
        for (size_t i = 0; i < size; i++)
            utf8string[i] = unicodedata[i];
    }
    
    ~UTF8String(void)
    {
        if (utf8string != 0)
            delete utf8string;
    }
    
    operator RString () { return utf8string; }
    
    operator char* () { return utf8string; }
    
    operator const char* const () { return utf8string; }
    
    operator const RString const () { return utf8string; }
    
private:
    char* utf8string;
};
*/
}

#define UNISTRING(X) L##X
#define UTF8String(X) L##X
#define UTF8(X) L##X
#define ENO_UNICODE
//*/
// }
#endif

#if !defined(interface)
#define interface class
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
