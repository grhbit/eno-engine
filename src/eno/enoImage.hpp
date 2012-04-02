/*
*  enoImage.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 11. 23..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoReferenceCounter.hpp"
#include "enoGraphics.hpp"
#include "enoGraphicsType.hpp"
#include "size2d.hpp"
#include "colorType.hpp"

namespace eno {

    class enoImage : public enoReferenceCounter
    {
    public:

//      enoImage( void );

        enoImage( ColorFormat, core::size2d_template<u32> );

        ~enoImage( void );

        u8* lock( void );

        void unlock( void );

        void bind( u8* buffer );

        core::size2d_template<u32> getSize( void ) const;

        void setSize(core::size2d_template<u32> size_) { size = size_; }

        u32 getWidth( void ) const;

        u32 getHeight( void ) const;

        void setPixel( core::colorTypeF, core::position2d_template<u32> );

        core::colorTypeF getPixel(core::position2d_template<u32>);

        void setColorFormat(ColorFormat format) { colorformat = format; }
        
        ColorFormat getColorFormat( void ) const;

    private:
        u8* data;
        ColorFormat colorformat;
        core::size2d_template<u32> size;
    };

}