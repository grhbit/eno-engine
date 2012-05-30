//
//  ImageLoader_Png.cpp
//  eno
//
//  Created by GWON SEONG GWANG on 12. 5. 30..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#include "ImageLoader_Png.hpp"
#include "enoFile.hpp"
#include "libpng/png.h"

namespace eno {
    
    void PNGAPI user_read_data_fn(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        png_size_t check;
    }
    
    enoImage* ImageLoader_PNG::loadImage(const eno::TextureID & ID)
    {
        enoFile file;
        file.open(ID.filename, enoFile::READ|enoFile::BINARY);
        
        if(!file.isOpen()) {
            return nullptr;
        }
        
        png_structp png_ptr;
        png_infop info_ptr;
        png_uint_32 width, height;
        int bit_depth, color_type, interlace_type;
        
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        
        if (png_ptr) {
            return nullptr;
        }
        
        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == nullptr)
        {
            png_destroy_read_struct(&png_ptr, NULL, NULL);
            return nullptr;
        }
        
        png_set_read_fn(png_ptr, (void *)&file, user_read_data_fn);
        
        enoImage* image = nullptr;
        
        return image;
    }
    
}