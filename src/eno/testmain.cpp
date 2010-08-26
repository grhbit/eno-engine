/*
 *  testmain.cpp
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma warning(disable: 4819)
#include "enoConfig.h"

#ifdef ENO_WINDOWS_PLATFORM
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "glut.h"

#pragma comment(lib, "glut32d.lib")
#endif

#include "enoType.h"
#include "matrix4x4.h"
#include <iostream>
using namespace std;

using namespace eno;
using namespace core;

bool enotypeTest();
bool enoMatrixMathTest();
bool enoVectorMathTest();

#ifdef ENO_MACOSX_PLATFORM
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

GLuint texture = 0;

void displayfunc( void )
{
	//*
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0); glVertex2d(-1.0, -1.0);
	glTexCoord2d(1.0, 0.0); glVertex2d(+1.0, -1.0);
	glTexCoord2d(1.0, 1.0); glVertex2d(+1.0, +1.0);
	glTexCoord2d(0.0, 1.0); glVertex2d(-1.0, +1.0);
	glEnd();
	//*/
}

GLuint createTexture()
{
	GLuint tex = 0;
	u8* data;
	
	u32 width, height;
	
	width = 256;
	height = 256;

	data= new u8[width*height*3];
	
	for (u32 i = 0; i<(width*height*3) ; i+=3) {
		data[i] = 0;
		data[i+1] = 0;
		data[i+2] = 0;
	}
	
	glGenTextures(1, &tex);
	
	glBindTexture(GL_TEXTURE_2D, tex);
	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	
	// when texture area is small, bilinear filter the closest MIP map
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the first MIP map
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	delete []data;

	return tex;
}

int main( int argc, char** argv )
{
//  	glutInit(&argc, argv);
//  	glutInitWindowSize(800, 600);
//  	glutInitDisplayMode(GLUT_DOUBLE);
//  
//  	int win = glutCreateWindow(argv[0]);
//  	glutDisplayFunc(displayfunc);
//  	glClearColor(0, 0, 0, 0);
//  	texture = createTexture();
//  	glutMainLoop();
//  	
//  	glDeleteTextures(1, &texture);
//  	
//  	glutDestroyWindow(win);
	{
		if(enotypeTest() == false)
			cout<<"enoTypeTest Failed."<<endl;

		if(enoMatrixMathTest() == false)
			cout<<"enoMatrixMathTest Failed."<<endl;

		if(enoVectorMathTest() == false)
			cout<<"enoVectorMathTest Failed."<<endl;
		
	}
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

#include <d3d9.h>
#include <d3dx9.h>
#pragma  comment(lib, "d3dx9d.lib")
#include "vector3d.h"

bool enoMatrixMathTest()
{
	return true;
}

bool enoVectorMathTest()
{
	D3DXVECTOR3 vec, lhs, rhs;

	lhs = D3DXVECTOR3(2.0f, 1.0f, 3.0f);
	rhs = D3DXVECTOR3(1.0f, 1.0f, 10.0f);

	for (float t = 0.0f; t < 100.0f; t++)
	{
		D3DXVec3Scale(&vec, &lhs, t);
	}
	

	return true;
}