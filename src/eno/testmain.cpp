/*
 *  testmain.cpp
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#include "enoType.h"
#include "matrix4.h"
#include <iostream>
using namespace std;


bool enotypeTest()
{
	if (sizeof(eno::u8) != 1) {
		return false;
	}
	if (sizeof(eno::s8) != 1) {
		return false;
	}
	if (sizeof(eno::c8) != 1) {
		return false;
	}
	if (sizeof(eno::u16) != 2) {
		return false;
	}
	if (sizeof(eno::s16) != 2) {
		return false;
	}
	if (sizeof(eno::u32) != 4) {
		return false;
	}
	if (sizeof(eno::s32) != 4) {
		return false;
	}
	if (sizeof(eno::u64) != 8) {
		return false;
	}
	if (sizeof(eno::s64) != 8) {
		return false;
	}
	
	return true;
}


int main( int argv, char** argc )
{
	__asm__ int 3;
	if(enotypeTest() == false)
		cout<<"enoTypeTest Failed."<<endl;
	
	eno::core::class_type::matrix4x4_template<eno::ftype> fMat;
	
	return 0;
}

