/*
*  GraphicsImpl_OGL.cpp
*  eno
*
*  Created by seonggwang.gwon on 12. 2. 3..
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
    
    OpenGLEnum::OpenGLEnum()
    {
        // --- No alpha channel
        TextureInfo[GraphicsEnum::ColorFMT_RGB5] = 
        TEXTUREINFO(GL_RGB5, GL_RGB, GL_UNSIGNED_SHORT_5_5_5_1);
        
        TextureInfo[GraphicsEnum::ColorFMT_RGB8] = 
        TEXTUREINFO(GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);
        
        TextureInfo[GraphicsEnum::ColorFMT_BGR8] = 
        TEXTUREINFO(GL_RGB8, GL_BGR, GL_UNSIGNED_BYTE);

        TextureInfo[GraphicsEnum::ColorFMT_BGRX8] = 
        TEXTUREINFO(GL_RGB, GL_BGRA, GL_UNSIGNED_BYTE);

        // --- Alpha channel
        TextureInfo[GraphicsEnum::ColorFMT_RGBA4] =
        TEXTUREINFO(GL_RGBA4, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4);
        
        TextureInfo[GraphicsEnum::ColorFMT_RGB5A1] = 
        TEXTUREINFO(GL_RGB5_A1, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1);
        
        TextureInfo[GraphicsEnum::ColorFMT_A1BGR5] = 
        TEXTUREINFO(GL_RGB5_A1, GL_ABGR_EXT, GL_UNSIGNED_SHORT_1_5_5_5_REV);
        
        TextureInfo[GraphicsEnum::ColorFMT_RGBA8] = 
        TEXTUREINFO(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
        
        TextureInfo[GraphicsEnum::ColorFMT_BGRA8] = 
        TEXTUREINFO(GL_RGBA8, GL_BGRA, GL_UNSIGNED_BYTE);
    }

    void GraphicsImpl_OGL::setCullMode(GraphicsEnum::CullMode cullmode)
    {
        if (cullmode == GraphicsEnum::CULL_NONE)
            glDisable(GL_CULL_FACE);
        else
        {
            glEnable(GL_CULL_FACE);
            glCullFace((cullmode == GraphicsEnum::CULL_BACK)? GL_BACK:GL_FRONT);
        }        
    }

    void GraphicsImpl_OGL::setLighting(bool b)
    {
        if (b)
            glEnable(GL_LIGHTING);
        else
            glDisable(GL_LIGHTING);
        
    }

    void GraphicsImpl_OGL::create(GraphicsMode mode)
    {
        OpenGLArchInit(mode);

        glViewport(0, 0, mode.width, mode.height); 

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
//      gluPerspective(45.0f,(GLfloat)Property.Width/(GLfloat)Property.Height,0.1f,100.0f);
        glOrtho(-1, 1, -1, 1, 0, 100);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
/*
        glShadeModel(GL_SMOOTH);
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
*/
        glClearColor(0.0, 0.3f, 0.5f, 0.5f);
        glClearDepth(1.0f);
    }

    void GraphicsImpl_OGL::destroy(void)
    {
        OpenGLArchClose;
    }
    
    void GraphicsImpl_OGL::setTexture(const eno::enoTexture *texture, u32 index)
    {
        GLuint tex = 0;
        if (texture != nullptr) {
            tex = texture->getTexture();
        }
        
        glBindTexture(GL_TEXTURE_2D, tex);
    }
    
    void GraphicsImpl_OGL::drawPoints(const spriteVertex v[], f32 size, s32 count)
    {
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        
        glPointSize(size);
        glVertexPointer(3, GL_FLOAT, sizeof(spriteVertex), &v->p);
        glColorPointer(4, GL_FLOAT, sizeof(spriteVertex), &v->c);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        {
            glDrawArrays(GL_POINTS, 0, count);
        }
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }
    
    void GraphicsImpl_OGL::drawLines(const spriteVertex v[], f32 width, s32 numVerts)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        glLineWidth(width);
        glVertexPointer(3, GL_FLOAT, sizeof(spriteVertex), &v->p);
        glColorPointer(4, GL_FLOAT, sizeof(spriteVertex), &v->c);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        {
            glDrawArrays(GL_LINES, 0, numVerts);
        }
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }
    
    void GraphicsImpl_OGL::drawPolygons(const modelVertex v[], s32 numPolygons)
    {
        glVertexPointer(3, GL_FLOAT, sizeof(modelVertex), &v->p);
        glColorPointer(4, GL_FLOAT, sizeof(modelVertex), &v->c);
        glTexCoordPointer(2, GL_FLOAT, sizeof(modelVertex), &v->t);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        {
            glDrawArrays(GL_TRIANGLES, 0, numPolygons);
        }
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    
    void GraphicsImpl_OGL::drawQuad(const spriteVertex[])
    {
        
    }
}