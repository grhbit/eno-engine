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
#include <GL/GL.h>
#include <GL/GLU.h>

namespace eno {

    class GraphicsImpl_OGL : public GraphicsImpl
    {
    private:
        /* virtual */ void setCullMode(CullMode);

        /* virtual */ void setLighting(boolean);

        /* virtual */ void create(GraphicsMode);

        /* virtual */ void destroy(void);

    };

}