/*
*  enoTexture.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 8. 27..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoType.hpp"
#include "size2d.hpp"
#include "enoGraphicsType.hpp"
#include "enoReferenceCounter.hpp"

namespace eno {

    class enoImage;
    interface enoTexture : public enoReferenceCounter
    {
    public:
        enoTexture( void ) { }
        
        virtual ~enoTexture( void ) { }
        
        void init( core::size2d_template<u32> size, GraphicsEnum::ColorFormat format,
                  u8* data = 0 ) { Init(size, format, data); }
        
        u8* lock( u32 index = 0 ) { return Lock(index); }
        
        void unlock( u32 index = 0 ) { Unlock(index); }
        
        void bind( u8* buffer, u32 index = 0 ) { Bind(buffer, index); }
        
        enoImage* getImage( u32 index = 0 ) const { return GetImage(index); }
        
        u32 getTexture() const { return GetTexture(); }
        
    protected:
        virtual void Init( core::size2d_template<u32> size, GraphicsEnum::ColorFormat format,
                          u8* data ) = 0;
        
        virtual u8* Lock( u32 index ) = 0;
        
        virtual void Unlock( u32 index ) = 0;
        
        virtual void Bind( u8* buffer, u32 index ) = 0;
        
        virtual enoImage* GetImage( u32 index ) const = 0;
        
        virtual u32 GetTexture() const = 0;
    };
}
