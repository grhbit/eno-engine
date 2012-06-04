/*
*  ImageLoader_BMP.hpp
*  eno
*
*  Created by seonggwang.gwon on 12. 2. 26..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoImageLoader.hpp"

namespace eno {

    class ImageLoader_BMP : public enoImageLoader
    {
    private:
        /* virtual */ RString getLoaderType() { return "BMP"; }

        /* virtual */ enoImage* loadImage(const TextureID&);
    };

}