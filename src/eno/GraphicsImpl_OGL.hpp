/*
*  GraphicsImpl_OGL.hpp
*  eno
*
*  Created by seonggwang.gwon on 12. 2. 3..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include <tuple>

#include "GraphicsImpl.hpp"
#if defined(ENO_MACOSX_PLATFORM)
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#else
#include <GL/GL.h>
#include <GL/GLU.h>
#endif

namespace eno {
    
    static const struct OpenGLEnum {
        enum { INTERNAL_FORMAT = 0, FORMAT, TYPE };
        typedef std::tuple<GLint, GLenum, GLenum, int> TEXTUREINFO;
        TEXTUREINFO TextureInfo[GraphicsEnum::ColorFormat_Count];
        OpenGLEnum();
    } OpenGL;

    class GraphicsImpl_OGL : public GraphicsImpl
    {
    public:
    private:
        /* virtual */ void setCullMode(GraphicsEnum::CullMode);
        /* virtual */ void setLighting(bool);

        /* virtual */ void create(GraphicsMode);
        /* virtual */ void destroy(void);
        
        /* virtual */ void setTexture(const enoTexture*, u32);

        /* virtual */ void drawPoints(const spriteVertex[], f32, s32);
        /* virtual */ void drawLines(const spriteVertex[], f32, s32);
        /* virtual */ void drawPolygons(const modelVertex[], s32);
        /* virtual */ void drawQuad(const spriteVertex[]);
    };

}