/*
 *  enoTypeTest.cpp
 *  eno
 *
 *  Created by seonggwang.gwon on 11. 1. 19..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "enoType.hpp"
#include "enoTypeTest.h"

namespace {
	TEST(enoTypeTest)
	{
		CHECK(sizeof(eno::u8) == 1);
		CHECK(sizeof(eno::s8) == 1);
		CHECK(sizeof(eno::c8) == 1);
		
		CHECK(sizeof(eno::u16) == 2);
		CHECK(sizeof(eno::s16) == 2);
		
		CHECK(sizeof(eno::u32) == 4);
		CHECK(sizeof(eno::s32) == 4);
		
		CHECK(sizeof(eno::u64) == 8);
		CHECK(sizeof(eno::s64) == 8);
	}
}
