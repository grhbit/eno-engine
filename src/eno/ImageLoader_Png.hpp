//
//  ImageLoader_Png.hpp
//  eno
//
//  Created by seonggwang.gwon on 12. 5. 30..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#pragma once
#include "enoImageLoader.hpp"

namespace eno {
    
    class ImageLoader_PNG : public enoImageLoader
    {
    private:
        /* virtual */ RString getLoaderType() { return "PNG"; }
        
        /* virtual */ enoImage* loadImage(const TextureID&);
    };
    
}