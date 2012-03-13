/*
*  enoGraphics.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 8. 23..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoReferenceCounter.hpp"
#include "enoType.hpp"
#include "enoGraphicsType.hpp"

namespace eno {

    struct GraphicsMode
    {
    public:
        GraphicsMode( void ): 
          width(0), height(0), bpp(0), windowed(false), vsync(false) {}

        GraphicsMode( s16 Width, s16 Height, s16 Bpp, boolean Windowed, boolean Vsync ):
          width(Width), height(Height), bpp(Bpp), windowed(Windowed), vsync(Vsync) {}

    public:
        s16 width;
        s16 height;
        u16 bpp;
        boolean windowed;
        boolean vsync;
    };

    class GraphicsImpl;

    interface enoGraphics
    {
    public:
        enoGraphics( void );
        ~enoGraphics( void );

        void setCullMode(CullMode cullmode);
        void setLighting(boolean);

        void reset(GraphicsMode mode);

        void create(GraphicsMode mode);
        void destroy(void);
    public:
        static enoGraphics* getInstance( void );
        static void release( void );

    private:
        static enoGraphics* instance;
        GraphicsImpl* unit;

    };

    static enoAutoPtr_<enoGraphics> GRAPHICS(false, enoGraphics::getInstance, enoGraphics::release);

}