/*
*  GraphicsImpl.hpp
*  eno
*
*  Created by seonggwang.gwon on 12. 2. 3..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoGraphics.hpp"

namespace eno {

    class GraphicsImpl
    {
        friend interface enoGraphics;
    public:
        
    protected:
        GraphicsImpl(void) { }
        
        virtual ~GraphicsImpl(void) { }

        virtual void setCullMode(CullMode) = 0;
        virtual void setLighting(bool) = 0;

        virtual void create(GraphicsMode) = 0;
        virtual void destroy(void) = 0;
        
        virtual void drawPoints(const spriteVertex[], f32, s32) = 0;
        virtual void drawLines(const spriteVertex[], f32, s32) = 0;
        virtual void drawPolygons(const modelVertex[], s32) = 0;
        virtual void drawQuad(const spriteVertex[]) = 0;
    };

}