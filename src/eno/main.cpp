/*
 *  main.cpp
 *  eno
 *
 *  Created by seonggwang.gwon on 11. 1. 19..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "eno.hpp"

#if defined(ENO_MACOSX_PLATFORM)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <unistd.h>
#elif defined(ENO_WINDOWS_PLATFORM)
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "enoApplication.hpp"
#include "enoMath.hpp"
#include "enoWindow.hpp"
#include "enoTimer.hpp"
#include "enoGraphics.hpp"
#include "enoFile.hpp"
#include "enoImageLoader.hpp"
#include "ImageLoader_BMP.hpp"
#include "ImageLoader_PNG.hpp"
#include "Texture_OGL.hpp"
#include "quaternion.hpp"
#include "GraphicsImpl_OGL.hpp"
using namespace eno;

enoImageLoader* imageloader;
enoImage* image;
enoTexture* texture;

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
    glShadeModel(GL_FLAT);
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
//*
    glEnable(GL_TEXTURE_2D);  
//    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL );    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    GRAPHICS->setTexture(texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);glColor4f(1, 1, 1, 1);glVertex3f(-1,-1, 0);
    glTexCoord2f(0,1);glColor4f(1, 1, 1, 1);glVertex3f(-1, 1, 0);  
    glTexCoord2f(1,1);glColor4f(1, 1, 1, 1);glVertex3f( 1, 1, 0);  
    glTexCoord2f(1,0);glColor4f(1, 1, 1, 1);glVertex3f( 1,-1, 0);  
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //*/
//    glRasterPos2f(-1,-1);
//    glDrawPixels(image->getWidth(), image->getHeight(), std::get<OpenGLEnum::FORMAT>(OpenGL.TextureInfo[image->getColorFormat()]), std::get<OpenGLEnum::TYPE>(OpenGL.TextureInfo[image->getColorFormat()]), image->lock());

    GRAPHICS->drawPoint(spriteVertex(core::vector3d(sin(sinv),-cos(sinv),0), core::colorTypeF(cos(sinv)*cos(sinv)*0.5,cos(sinv)*cos(sinv)*0.5,1,1), core::vector2d(0,0)), 1000);
    GRAPHICS->drawLine(spriteVertex(core::vector3d(-1,-1,0),core::colorTypeF(cos(sinv)*cos(sinv),0,cos(sinv)*cos(sinv),1), core::vector2d(0,0)),spriteVertex(core::vector3d(1,1,0),core::colorTypeF(1,cos(sinv)*cos(sinv),cos(sinv)*cos(sinv),1), core::vector2d(0,0)), 10);

    glFlush();
}

bool Update(f32)
{
    return true;
}

using namespace std;
int main(int, char *argv[])
{
//
    //temporary code
#if defined(ENO_MACOSX_PLATFORM)
    chdir("../Visual Studio");
#endif

    imageloader = new ImageLoader_BMP;
    TextureID ID;
    ID.filename = "dummy.bmp";
    image = imageloader->loadImage(ID);
// /
    enoWindowProperty property(800, 600, "eno10.0", false, Update, Draw);

    APP->initialize(property);
/*
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_BGRA, GL_UNSIGNED_SHORT_1_5_5_5_REV, image->lock());
    */
    texture = new Texture_OGL;
    texture->init(image->getSize(), image->getColorFormat(), image->lock());
    image->unlock();
    // /
    APP->mainLoop();
//
    delete texture;
    delete image;
    delete imageloader;
//*/
    return 0;
}
