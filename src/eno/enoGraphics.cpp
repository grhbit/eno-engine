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

}