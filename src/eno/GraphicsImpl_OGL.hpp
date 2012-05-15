/*
*  GraphicsImpl_OGL.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 3..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "GraphicsImpl.hpp"
#if defined(ENO_MACOSX_PLATFORM)
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#else
#include <GL/GL.h>
#include <GL/GLU.h>
#endif

namespace eno {

    class GraphicsImpl_OGL : public GraphicsImpl
    {
    private:
        /* virtual */ void setCullMode(CullMode);
        /* virtual */ void setLighting(boolean);

        /* virtual */ void create(GraphicsMode);
        /* virtual */ void destroy(void);

        /* virtual */ void drawPoints(const spriteVertex[], f32, s32);
        /* virtual */ void drawLines(const spriteVertex[], f32, s32);
        /* virtual */ void drawPolygons(const modelVertex[], s32);
        /* virtual */ void drawQuad(const spriteVertex[]);
    };

}