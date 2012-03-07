/*
*  GraphicsImpl.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 3..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoGraphics.hpp"

namespace eno {

    class GraphicsImpl
    {
        friend class enoGraphics;
    public:

    protected:
        GraphicsImpl(void) { }

        virtual void setCullMode(CullMode) = 0;

        virtual void setLighting(boolean) = 0;

        virtual void create(GraphicsMode) = 0;

        virtual void destroy(void) = 0;
    };

}