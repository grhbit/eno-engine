/*
 *  enoType.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "enoConfig.h"


ENO_NAMESPACE_BEGIN

	//8-Byte
	typedef unsigned char u8;

	typedef char c8;

	typedef char s8;

	//16-Byte
	typedef unsigned short u16;

	typedef short s16;

	//32-Byte
	typedef unsigned int u32;

	typedef int s32;

	typedef float f32;

	//64-Byte
	typedef unsigned long long u64;

	typedef long long s64;

	typedef double f64;

	//In case template, decide type!

	typedef f32 ftype;

ENO_NAMESPACE_END


