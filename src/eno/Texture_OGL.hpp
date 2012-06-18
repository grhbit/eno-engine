/*
*  Texture_OGL.hpp
*  eno
*
*  Created by seonggwang.gwon on 11. 2. 24..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoTexture.hpp"

namespace eno {

    class Texture_OGL : public enoTexture
    {
    public:
        Texture_OGL();
        ~Texture_OGL();
        
    private:
        /* virtual */ void Init( core::size2d_template<u32> size, GraphicsEnum::ColorFormat format,
                                u8* data );

        /* virtual */ u8* Lock( u32 index );

        /* virtual */ void Unlock( u32 index );

        /* virtual */ void Bind( u8* buffer, u32 index );

        /* virtual */ enoImage* GetImage( u32 index ) const;
        
        /* virtual */ u32 GetTexture() const;

        enoImage* image;
        u32 tex;
    };

}