/*
*  enoGraphics.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 8. 23..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoReferenceCounter.hpp"
#include "enoType.hpp"
#include "enoGraphicsType.hpp"
#include "enoTexture.hpp"

namespace eno {

    interface enoTexture;
    
    struct GraphicsMode
    {
    public:
        GraphicsMode( void ): 
          width(0), height(0), bpp(0), windowed(false), vsync(false) {}

        GraphicsMode( s16 Width, s16 Height, s16 Bpp, bool Windowed, bool Vsync ):
          width(Width), height(Height), bpp(Bpp), windowed(Windowed), vsync(Vsync) {}

    public:
        s16 width;
        s16 height;
        u16 bpp;
        bool windowed;
        bool vsync;
    };

    class GraphicsImpl;

    interface enoGraphics
    {
    public:
        enoGraphics( void );
        ~enoGraphics( void );

        void setCullMode(GraphicsEnum::CullMode cullmode);
        void setLighting(bool);

        void reset(GraphicsMode mode);

        void create(GraphicsMode mode);
        void destroy(void);
        
        void setTexture(const enoTexture*, u32 index=0);
        
        void drawPoint(const spriteVertex& pos, f32 size);
        void drawPoints(const spriteVertex v[], f32 size, s32 count);
        void drawLine(const spriteVertex& start, const spriteVertex& end, f32 width);
        void drawLines(const spriteVertex v[], f32 width, s32 numVerts);
        void drawPolygon(const modelVertex v[]);
        void drawPolygons(const modelVertex v[], s32 numPolygons);
        void drawQuad(const spriteVertex v[]);
        void drawQuad(const core::rectangle&);
        void drawQuads(const spriteVertex v[], s32 numQuads);
    public:
        static enoGraphics* getInstance( void );
        static void release( void );

    private:
        static enoGraphics* instance;
        GraphicsImpl* unit;

    };

    extern enoAutoPtr_<enoGraphics> GRAPHICS;

}