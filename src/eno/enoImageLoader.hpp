/*
*  enoImageLoader.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 11. 23..
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

        virtual CString getLoaderType(void) = 0;

        virtual enoImage* loadImage(const TextureID&) = 0;
    };

}