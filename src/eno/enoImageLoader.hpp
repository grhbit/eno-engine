/*
*  enoImageLoader.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 11. 23..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoReferenceCounter.hpp"
#include "enoImage.hpp"

namespace eno {

    interface enoImageLoader : public enoReferenceCounter
    {
    public:
        virtual ~enoImageLoader( void ) { }

        virtual RString getLoaderType(void) = 0;

        virtual enoImage* loadImage(const TextureID&) = 0;
    };

}