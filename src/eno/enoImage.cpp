/*
*  enoImage.cpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 3. 3..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#include "enoImage.hpp"

namespace eno {

    enoImage::enoImage(void) : data(nullptr), colorformat(ColorFormat_Count), size(0, 0)
    {
    }

    enoImage::enoImage(u8* buffer, ColorFormat colorFMT, core::size2d_template<u32> size_)
        : data(buffer), colorformat(colorFMT), size(size_) 
    {

    }

    enoImage::~enoImage(void)
    {
        if (data != nullptr)
            delete []data;
    }

    u8* enoImage::lock(void)
    {
        return data;
    }

    void enoImage::unlock()
    {
    }

    void enoImage::bind(u8* buffer)
    {
        data = buffer;
    }

    core::size2d_template<u32> enoImage::getSize(void) const
    {
        return size;
    }

    u32 enoImage::getWidth(void) const
    {
        return getSize().getWidth();
    }

    u32 enoImage::getHeight(void) const
    {
        return getSize().getHeight();
    }

    void enoImage::setPixel(core::colorTypeF color, core::position2d_template<u32>)
    {
    }

    core::colorTypeF enoImage::getPixel(core::position2d_template<u32>)
    {
        return core::colorTypeF();
    }

    ColorFormat enoImage::getColorFormat(void) const
    {
        return colorformat;
    }
}