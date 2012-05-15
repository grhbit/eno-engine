//
//  enoGraphics.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 12. 1. 18..
//  Copyright (c) 2012 g.passcode@gmail.com . All rights reserved.
//

#include "enoGraphics.hpp"
#include "GraphicsImpl.hpp"
#include "GraphicsImpl_OGL.hpp"

namespace eno {
    
    enoGraphics* enoGraphics::instance = nullptr;

    enoGraphics::enoGraphics( void )
    {
        unit = new GraphicsImpl_OGL;
    }
    
    enoGraphics::~enoGraphics( void )
    {
        delete unit;
    }

    enoGraphics* enoGraphics::getInstance( void )
    {
        if (instance == nullptr)
        {
            instance = new enoGraphics;
        }
        return instance;
    }

    void enoGraphics::release( void )
    {
        if (instance != nullptr)
        {
            delete instance;
            instance = nullptr;
        }
    }

    void enoGraphics::setCullMode( CullMode cullmode )
    {
        if(ENUM_INVALID_CHECK(CullMode, cullmode))
            unit->setCullMode(cullmode);
    }

    void enoGraphics::setLighting(boolean b)
    {
        unit->setLighting(b);
    }

    void enoGraphics::reset(GraphicsMode mode)
    {
        destroy();
        create(mode);
    }

    void enoGraphics::create( GraphicsMode mode )
    {
        unit->create(mode);
    }

    void enoGraphics::destroy( void )
    {
        unit->destroy();
    }

    void enoGraphics::drawPoint(const spriteVertex& pos, f32 size)
    {
        if (size>0) {
            this->drawPoints(&pos, size, 1);
        }
    }
    
    void enoGraphics::drawPoints(const spriteVertex v[], f32 size, s32 count)
    {
        if (size>0 && count>0) {
            unit->drawPoints(v, size, count);
        }
    }
    
    void enoGraphics::drawLine(const spriteVertex& start, const spriteVertex& end, f32 width)
    {
		static spriteVertex v[2];
        if (width>0) {
			v[0] = start;
			v[1] = end;
            this->drawLines(v, width, 2);
        }
    }
    
    void enoGraphics::drawLines(const spriteVertex v[], f32 width, s32 numVerts)
    {
        if (width>0 && numVerts>=2) {
            unit->drawLines(v, width, numVerts);
        }
    }
    
    void enoGraphics::drawPolygon(const modelVertex v[])
    {
        drawPolygons(v, 3);
    }
    
    void enoGraphics::drawPolygons(const modelVertex v[], s32 numPolygons)
    {
        if (numPolygons%3 != 0) {
            return;
        }
        unit->drawPolygons(v, numPolygons);
    }
    
    void enoGraphics::drawQuad(const spriteVertex v[])
    {
        unit->drawQuad(v);
    }
    
}