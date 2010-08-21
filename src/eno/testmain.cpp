/*
 *  testmain.cpp
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma warning(disable: 4819)

#include "enoType.h"
#include "matrix4x4.h"
#include <iostream>
using namespace std;


using namespace eno;
using namespace core;

bool enotypeTest();
bool enoMatrixMathTest();

int main( int argv, char** argc )
{
	if(enotypeTest() == false)
		cout<<"enoTypeTest Failed."<<endl;

	if(enoMatrixMathTest() == false)
		cout<<"enoMatrixMathTest Failed."<<endl;
	
	return 0;
}


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

bool enoMatrixMathTest()
{
	matrix4x4 mat, lm, rm;

	mat.makeRotate(1.2f,1.3f,1.4f);
	mat.identity();

	mat.rotateZ(1.4f);
	mat.rotateY(1.3f);
	mat.rotateX(1.2f);

	mat.makeRotateYawPitchRoll(1.2f,1.3f,1.4f);

	return true;
}