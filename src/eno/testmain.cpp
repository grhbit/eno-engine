/*
 *  testmain.cpp
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#include "enoType.h"
#include "matrix4x4.h"
#include <iostream>
using namespace std;


using namespace eno;
using namespace core;

bool enotypeTest();

int main( int argv, char** argc )
{
	if(enotypeTest() == false)
		cout<<"enoTypeTest Failed."<<endl;
	
	matrix4x4_template<f32> mat;
	
	matrix4x4_template<f32> sca;
	
	mat.multiplyLocal(matrix4x4_template<f32>::MakeRotateZ(3.0f));
	mat.multiplyLocal(matrix4x4_template<f32>::MakeRotateY(2.0f));
	mat.multiplyLocal(matrix4x4_template<f32>::MakeRotateX(1.0f));
	
	sca.makeRotate(vector3_template<f32>(1.0f, 2.0f, 3.0f));
	
	matrixUtil<f32>::multiply = multMatrixSSE;
	
	mat.multiply(sca);
	
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
