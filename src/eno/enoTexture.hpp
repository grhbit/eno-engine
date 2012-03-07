/*
*  enoTexture.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 8. 27..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoImage.hpp"

namespace eno {
    

interface enoTexture : public enoReferenceCounter
{
public:

    enoTexture( void ) { }

    virtual ~enoTexture( void ) { }

    void init( core::size2d size, u8* data = 0 ) { Init(size, data); }

    u8* lock( u32 index = 0 ) { return Lock(index); }

    void unlock( u32 index = 0 ) { Unlock(index); }

    void bind( u8* buffer, u32 index = 0 ) { Bind(buffer, index); }

    enoImage* getImage( u32 index = 0 ) const { return GetImage(index); }

protected:
    virtual void Init( core::size2d size, u8* data ) = 0;

    virtual u8*	Lock( u32 index ) = 0;

    virtual void Unlock( u32 index ) = 0;

    virtual void Bind( u8* buffer, u32 index ) = 0;

    virtual enoImage* GetImage( u32 index ) const = 0;
};

}

    // 2:33