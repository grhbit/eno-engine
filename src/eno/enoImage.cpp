/*
*  enoImage.cpp
*  eno
*
*  Created by seonggwang.gwon on 12. 3. 3..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#include "enoImage.hpp"

namespace eno {
/*
    enoImage::enoImage(void) : data(nullptr), colorformat(ColorFormat_Count), size(0, 0)
    {
    }
*/

    enoImage::enoImage(GraphicsEnum::ColorFormat colorFMT, core::size2d_template<u32> size_)
        : data(nullptr), colorformat(colorFMT), size(size_) 
    {
        //*
        if (ENUM_INVALID_CHECK(GraphicsEnum::ColorFormat, colorFMT)) {
            data = new u8[size.getArea() * std::get<GraphicsEnum::DEPTH>(Graphics.ColorFormatInfo[colorFMT])/8];
        }
        //*/
        /*
        if((colorformat == GraphicsEnum::ColorFMT_A1BGR5)||
           (colorformat == GraphicsEnum::ColorFMT_RGB5A1)||
           (colorformat == GraphicsEnum::ColorFMT_RGBA4) ||
           (colorformat == GraphicsEnum::ColorFMT_RGB5))
        {
            data = new u8[size.getArea() * sizeof(u8) * 2];
        }
        else if
          ((colorformat == GraphicsEnum::ColorFMT_BGR8) ||
           (colorformat == GraphicsEnum::ColorFMT_RGB8))
        {
            data = new u8[size.getArea() * sizeof(u8) * 3];
        }
        else
        {
            data = new u8[size.getArea() * sizeof(u8) * 4];
        }
         //*/
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

    GraphicsEnum::ColorFormat enoImage::getColorFormat(void) const
    {
        return colorformat;
    }
}