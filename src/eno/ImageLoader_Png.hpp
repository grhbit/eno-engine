//
//  ImageLoader_Png.hpp
//  eno
//
//  Created by GWON SEONG GWANG on 12. 5. 30..
//  Copyright (c) 2012년 g.passcode@gmail.com. All rights reserved.
//

#pragma once
#include "enoImageLoader.hpp"

namespace eno {
    
    class ImageLoader_PNG : public enoImageLoader
    {
    private:
        /* virtual */ CString getLoaderType() { return "PNG"; }
        
        /* virtual */ enoImage* loadImage(const TextureID&);
    };
    
}