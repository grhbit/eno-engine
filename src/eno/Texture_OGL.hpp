/*
*  Texture_OGL.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 11. 2. 24..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoTexture.hpp"

namespace eno {

    class Texture_OGL : public enoTexture
    {
    private:
        /* virtual */ void Init(  core::size2d size, u8* data );

        /* virtual */ u8* Lock( u32 index );

        /* virtual */ void Unlock( u32 index );

        /* virtual */ void Bind( u8* buffer, u32 index );

        /* virtual */ enoImage* GetImage( u32 index );

        u32 tex;
    };

}