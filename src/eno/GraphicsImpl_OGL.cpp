/*
*  GraphicsImpl_OGL.cpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 3..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#include "GraphicsImpl_OGL.hpp"

#ifdef ENO_WINDOWS_PLATFORM

#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>

class GraphicsOGLHelper_Windows
{
public:
    static void init(eno::GraphicsMode mode)
    {
        HWND hWnd = FindWindow(ENO_CLASS_NAME, NULL);
        HDC hDC = GetDC(hWnd);
        
        static PIXELFORMATDESCRIPTOR pfd = 
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1, // Version
            PFD_DRAW_TO_WINDOW |
            PFD_SUPPORT_OPENGL |
            PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            mode.bpp, // Color depth
            0, 0, 0, 0, 0, 0, // Color bits ignored
            0, // no Alpha buffer
            0, // Shift bit ignored
            0,
            0, 0, 0, 0,
            16,
            0,
            0,
            PFD_MAIN_PLANE,
            0, // Reserved
            0, 0, 0
        };

        GLuint PixelFormat;
        PixelFormat = ChoosePixelFormat(hDC, &pfd);
        SetPixelFormat(hDC, PixelFormat, &pfd);

        hRC = wglCreateContext(hDC);
        wglMakeCurrent(hDC, hRC);
    }

    static void close(void)
    {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hRC);
    }

private:
    static HGLRC hRC;
};

HGLRC GraphicsOGLHelper_Windows::hRC = NULL;

#define OpenGLArchInit(mode) GraphicsOGLHelper_Windows::init(mode)
#define OpenGLArchClose GraphicsOGLHelper_Windows::close()

#elif defined(ENO_MACOSX_PLATFORM)

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#define OpenGLArchInit(mode)
#define OpenGLArchClose

#endif

namespace eno {

    void GraphicsImpl_OGL::setCullMode(CullMode cullmode)
    {
        if (cullmode == CULL_NONE)
            glDisable(GL_CULL_FACE);
        else
        {
            glEnable(GL_CULL_FACE);
            glCullFace((cullmode == CULL_BACK)? GL_BACK:GL_FRONT);
        }        
    }

    void GraphicsImpl_OGL::setLighting(boolean b)
    {
        if (b)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
        
    }

    void GraphicsImpl_OGL::create(GraphicsMode mode)
    {
        OpenGLArchInit(mode);

        glMatrixMode(GL_VIEWPORT);
        glViewport(0, 0, mode.width, mode.height); 

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//      gluPerspective(45.0f,(GLfloat)Property.Width/(GLfloat)Property.Height,0.1f,100.0f);
        glOrtho(0, mode.width, 0, mode.height, 0, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);  
        glDepthFunc(GL_LEQUAL);   
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        glClearColor(0.0, 0.3f, 0.5f, 0.5f);
        glClearDepth(1.0f);
    }

    void GraphicsImpl_OGL::destroy(void)
    {
        OpenGLArchClose;
    }
}