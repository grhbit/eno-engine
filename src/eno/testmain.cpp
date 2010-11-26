/*
 *  testmain.cpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma warning(disable: 4819)
#include "enoConfig.h"

#ifdef ENO_WINDOWS_PLATFORM
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#endif

#include "enoType.h"
#include "matrix4x4.h"
#include <iostream>

#ifdef ENO_WINDOWS_PLATFORM
#include <d3d9.h>
#include <d3dx9.h>
#include "Core/DXUT.h"
#pragma  comment(lib, "d3dx9d.lib")
#pragma  comment(lib, "dxerr.lib")
#pragma comment(lib, "comctl32.lib")
#endif

#ifdef ENO_MACOSX_PLATFORM
#include <GLUT/GLUT.h>
#endif

#include "dimension2d.h"
#include "rectangle.h"
#include "UnitTest++.h"

using namespace std;

using namespace eno;
using namespace core;

bool enotypeTest();

GLuint tex = 0;

void displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(0.f, 1.f, 1.f);
	glLineWidth(15.f);
	
	glBegin( GL_LINES ); /* long edges of box */
	glVertex3f(  1.0,  0.6, -0.4 );   glVertex3f(  1.0,  0.6, 0.4 );
	glVertex3f(  1.0, -0.6, -0.4 );   glVertex3f(  1.0, -0.6, 0.4 );
	glVertex3f( -1.0, -0.6, -0.4 );   glVertex3f( -1.0, -0.6, 0.4 );
	glVertex3f( -1.0,  0.6, -0.4 );   glVertex3f( -1.0,  0.6, 0.4 );
	glEnd();
	
	glBegin( GL_LINE_LOOP ); /* end cap */
	glVertex3f(  1.0,  0.6, -0.4 ); glVertex3f(  1.0, -0.6, -0.4 );
	glVertex3f( -1.0, -0.6, -0.4 ); glVertex3f( -1.0,  0.6, -0.4 );
	glEnd();
	
	glBegin( GL_LINE_LOOP ); /* other end cap */
	glVertex3f(  1.0,  0.6, 0.4 ); glVertex3f(  1.0, -0.6, 0.4 );
	glVertex3f( -1.0, -0.6, 0.4 ); glVertex3f( -1.0,  0.6, 0.4 );
	glEnd();
	
	glFlush();
}

void textureLoading()
{
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

int main( int argc, char** argv )
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("eno window");
	glutDisplayFunc(displayFunc);
	glClearColor(0., 0., 0., 0.);
	glutMainLoop();

	UnitTest::RunAllTests();
	
	return 0;
}

namespace {

	TEST(enotypeTest)
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
