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
	
	int width, height;
	
	width = 256;
	height = 256;

	data= new u8[width*height*3];
	
	for (u32 i = 0; i<(width*height*3) ; i+=3) {
		data[i];
		data[i+1];
		data[i+2];
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
	glutInit(&argc, argv);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_DOUBLE);

	int win = glutCreateWindow(argv[0]);
	glutDisplayFunc(displayfunc);
	glClearColor(0, 0, 0, 0);
	texture = createTexture();
	glutMainLoop();
	
	glDeleteTextures(1, &texture);
	
	glutDestroyWindow(win);
	{
		if(enotypeTest() == false)
			cout<<"enoTypeTest Failed."<<endl;

		if(enoMatrixMathTest() == false)
			cout<<"enoMatrixMathTest Failed."<<endl;
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