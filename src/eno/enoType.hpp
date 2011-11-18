/*
 *  enoType.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoConfig.hpp"
#include <string>

ENO_NAMESPACE_BEGIN

	//1-Byte
	typedef unsigned char u8;

	typedef char c8;

	typedef char s8;

	//2-Byte
	typedef unsigned short u16;

	typedef short s16;

	//4-Byte
	typedef unsigned int u32;

	typedef int s32;

	typedef float f32;

	//8-Byte
	typedef unsigned long long u64;

	typedef long long s64;

	typedef double f64;

	//In case template, decide type!

	typedef f32 ftype;	//recommend type : f32

	//String type

	typedef std::string String;

	//Boolean type

	typedef u32 boolean;

	ENO_STRUCT_TYPE_BEGIN

	ENO_STRUCT_TYPE_END

ENO_NAMESPACE_END


