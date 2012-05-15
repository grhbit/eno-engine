/*
 *  main.cpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 11. 1. 19..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "Unittest++.h"
#include "enoUnitTest.h"
#include "eno.hpp"
#include "enoApplication.hpp"
#include "enoWindow.hpp"
#include "enoTimer.hpp"
#include "enoGraphics.hpp"
#include "enoFile.hpp"
#include "enoImageLoader.hpp"
#include "ImageLoader_BMP.hpp"
#include "quaternion.hpp"
using namespace eno;

enoImageLoader* imageloader;
enoImage* image;

#if defined(ENO_MACOSX_PLATFORM)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <unistd.h>
#elif defined(ENO_WINDOWS_PLATFORM)
#include <GL/gl.h>
#include <GL/glu.h>
#endif

GLuint tex;

void Draw(f32 delta)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //*

    static f64 time = 0;
    time += delta*0.7;
    
    static f64 sinv = 0;
    sinv = PI64*sin(time);
    
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glEnable(GL_TEXTURE_2D);  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glBindTexture(GL_TEXTURE_2D, tex);  
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glColor4f(1, 1, 1, 1);glVertex3f(-1,-1, 0);
    glTexCoord2f(0,1);glColor4f(1, 1, 1, 1);glVertex3f(-1, 1, 0);  
    glTexCoord2f(1,1);glColor4f(1, 1, 1, 1);glVertex3f( 1, 1, 0);  
    glTexCoord2f(1,0);glColor4f(1, 1, 1, 1);glVertex3f( 1,-1, 0);  
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    GRAPHICS->drawPoint(spriteVertex(core::vector3d(sin(sinv),-cos(sinv),0), core::colorTypeF(cos(sinv)*cos(sinv)*0.5,cos(sinv)*cos(sinv)*0.5,1,1), core::vector2d(0,0)), 1000);
    GRAPHICS->drawLine(spriteVertex(core::vector3d(-1,-1,0),core::colorTypeF(cos(sinv)*cos(sinv),0,cos(sinv)*cos(sinv),1), core::vector2d(0,0)),spriteVertex(core::vector3d(1,1,0),core::colorTypeF(1,cos(sinv)*cos(sinv),cos(sinv)*cos(sinv),1), core::vector2d(0,0)), 10);
    glFlush();
    // */
}

eno::boolean Update(f32)
{
    return true;
}


using namespace std;
int main(int, char *argv[])
{
//*
    //temporary code
#if defined(ENO_MACOSX_PLATFORM)
    chdir("../Visual Studio/");
#endif

    imageloader = new ImageLoader_BMP;
    TextureID ID;
    ID.filename = "dummy24.bmp";
    image = imageloader->loadImage(ID);
//* /
    enoWindowProperty property(800, 600, "eno10.0", false, Update, Draw);

    APP->initialize(property);
//*
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB8, GL_UNSIGNED_BYTE, image->lock());
    image->unlock();
    //* /
    APP->mainLoop();
//*
    glDeleteTextures(1, &tex);
    delete image;
    delete imageloader;
//*/
    return UnitTest::RunAllTests();
}
