//
//  enoGraphicsType.cpp
//  eno
//
//  Created by seonggwang.gwon on 12. 6. 8..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#include "enoGraphicsType.hpp"

namespace eno {

    GraphicsEnum::GraphicsEnum()
    {
        ColorFormatInfo[ColorFMT_RGB5X1] =
        COLORFORMAT_INFO(16, false);

        ColorFormatInfo[ColorFMT_X1BGR5] =
        COLORFORMAT_INFO(16, false);

        ColorFormatInfo[ColorFMT_RGB8] =
        COLORFORMAT_INFO(24, false);

        ColorFormatInfo[ColorFMT_BGR8] =
        COLORFORMAT_INFO(24, false);
        
        ColorFormatInfo[ColorFMT_RGBX8] =
        COLORFORMAT_INFO(32, false);
        
        ColorFormatInfo[ColorFMT_BGRX8] =
        COLORFORMAT_INFO(32, false);

        ColorFormatInfo[ColorFMT_RGBA4] =
        COLORFORMAT_INFO(16, true);

        ColorFormatInfo[ColorFMT_RGB5A1] =
        COLORFORMAT_INFO(16, true);

        ColorFormatInfo[ColorFMT_A1BGR5] =
        COLORFORMAT_INFO(16, true);

        ColorFormatInfo[ColorFMT_RGBA8] =
        COLORFORMAT_INFO(32, true);

        ColorFormatInfo[ColorFMT_BGRA8] =
        COLORFORMAT_INFO(32, true);

        /*
         ColorFMT_RGB5 = 0,
         ColorFMT_RGB8,
         ColorFMT_BGR8,
         
         // --- Alpha channel
         ColorFMT_RGBA4,
         ColorFMT_RGB5A1,
         ColorFMT_A1BGR5,
         ColorFMT_RGBA8,
         ColorFMT_BGRA8,
         ColorFormat_Count
         */
    }

}