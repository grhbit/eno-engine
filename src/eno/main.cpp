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
#elif defined(ENO_WINDOWS_PLATFORM)
#include <GL/gl.h>
#include <GL/glu.h>
#endif

GLuint tex;

void Draw(ftype)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glEnable(GL_TEXTURE_2D);  
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);  
    glBindTexture(GL_TEXTURE_2D, tex);  
    glBegin(GL_QUADS);  
    glTexCoord2f(0,0);glVertex3f(0,0, 0);  
    glTexCoord2f(0,1);glVertex3f(0, 100, 0);  
    glTexCoord2f(1,1);glVertex3f( 900, 100, 0);  
    glTexCoord2f(1,0);glVertex3f( 900,0, 0);  
    glEnd();  
    glFlush();  
    glDisable(GL_TEXTURE_2D); 
}

eno::boolean Update(ftype)
{
    return true;
}

using namespace std;
int main(int, char *argv[])
{
    /*
    chdir("../Visual Studio/");
    imageloader = new ImageLoader_BMP;
    TextureID ID;
    ID.filename = "dummy24.bmp";
    image = imageloader->loadImage(ID);
*/
    enoWindowProperty property(900, 100, "eno10.0", false, Update, Draw);

    APP->initialize(property);
/*
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, image->lock());
    image->unlock();
*/
    APP->mainLoop();
/*
    glDeleteTextures(1, &tex);
    delete image;
    delete imageloader;
*/
    return UnitTest::RunAllTests();
}
