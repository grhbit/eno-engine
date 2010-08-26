﻿/*
 *  enoConfig.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 12..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */
#pragma once

#define ENO_MAJOR = 0
#define ENO_MINOR = 0
#define ENO_REVISION = 11

#define ENO_VERSION "0.0.11"

#include <stdio.h>

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

#if defined (ENO_WINDOW_DRIVER)
#define ENO_DISPLAY_DIRECT_9
#endif

#define ENO_DISPLAY_OPENGL

#if defined (_MSC_VER)
#define ENO_COMPILED_FROM_VISUAL_STUDIO

#elif defined (__GNUC__)
#define ENO_COMPILED_FROM_GNUC

#elif defined (__TURBOC__)
#elif defined (__BORLANDC__)
#elif defined (__WATCOMC__)
#elif defined (__IBMCPP__)
#endif

#ifdef ENO_COMPILED_FROM_VISUAL_STUDIO
#define ENO_ALIGNED_16 __declspec(align(16))
#else if ENO_COMPILED_FROM_GNUC
#define ENO_ALIGNED_16 __attribute__ ((aligned(16)))
#endif

#ifndef interface
#define interface struct
#endif


#define ENO_NAMESPACE_BEGIN	namespace eno {
#define ENO_NAMESPACE_END	}
#define ENO_CORE_NAMESPACE_BEGIN	namespace core {
#define ENO_CORE_NAMESPACE_END		}
#define ENO_DISPLAY_NAMESPACE_BEGIN namespace display {
#define ENO_DISPLAY_NAMESPACE_END	}

#define ENO_CLASS_TYPE_BEGIN	namespace class_type {
#define ENO_CLASS_TYPE_END		}
#define ENO_INTERFACE_TYPE_BEGIN	namespace interface_type {
#define ENO_INTERFACE_TYPE_END		}
#define ENO_STRUCT_TYPE_BEGIN	namespace struct_type {
#define ENO_STRUCT_TYPE_END		}
#define ENO_ENUM_TYPE_BEGIN		namespace enum_type {
#define ENO_ENUM_TYPE_END		}
#define ENO_FUNCTION_BEGIN		namespace function_type {
#define ENO_FUNCTION_END		}


#ifdef ENO_USING_NAMESPACE_TYPE
#undef ENO_USING_NAMESPACE_TYPE
#endif
#define ENO_USING_NAMESPACE_TYPE	\
	ENO_CLASS_TYPE_BEGIN			\
	ENO_CLASS_TYPE_END				\
	ENO_INTERFACE_TYPE_BEGIN		\
	ENO_INTERFACE_TYPE_END			\
	ENO_STRUCT_TYPE_BEGIN			\
	ENO_STRUCT_TYPE_END				\
	ENO_ENUM_TYPE_BEGIN				\
	ENO_ENUM_TYPE_END				\
	ENO_FUNCTION_BEGIN				\
	ENO_FUNCTION_END				\
	using namespace class_type;		\
	using namespace interface_type; \
	using namespace struct_type;	\
	using namespace enum_type;		\
	using namespace function_type;


ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_USING_NAMESPACE_TYPE
	ENO_CORE_NAMESPACE_END

	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_USING_NAMESPACE_TYPE
	ENO_DISPLAY_NAMESPACE_END

	ENO_USING_NAMESPACE_TYPE
ENO_NAMESPACE_END

// [skop 8:47 Friday. 8.13. 2010. Created.]
