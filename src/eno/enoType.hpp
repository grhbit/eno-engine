/*
*  enoType.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 8. 13..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoConfig.hpp"

namespace eno {
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

/*
//1-Byte
    using u8 = unsigned char;

    using c8 = char;

    using s8 = char;

//2-Byte
    using u16 = unsigned short;

    using s16 = short;

//4-Byte
    using u32 = unsigned int;

    using s32 = int;

    using f32 = float;

//8-Byte
    using u64 = unsigned long long;

    using s64 = long long;

    using f64 = double;
	*/
}