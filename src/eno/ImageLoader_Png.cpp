//
//  ImageLoader_Png.cpp
//  eno
//
//  Created by seonggwang.gwon on 12. 5. 30..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#include "libpng/png.h"
#include "libpng/pngstruct.h"

#include "ImageLoader_Png.hpp"
#include "enoFile.hpp"

namespace eno {
    
    void PNGAPI user_read_data_func(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        png_size_t check;
        enoFile *file = (enoFile *)png_ptr->io_ptr;
        check = (png_size_t) file->readBytes(data, length);
        
        if (check != length) {
            png_error(png_ptr, "Read Error");
        }
    }
    
    enoImage* ImageLoader_PNG::loadImage(const eno::TextureID & ID)
    {
        enoFile file;
        file.open(ID.filename, enoFile::READ);
        
        if(!file.is_open()) {
            return nullptr;
        }

        png_structp png_ptr;
        png_infop info_ptr;
        png_uint_32 width, height;
        int bit_depth, color_type, interlace_type;
        
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
        
        if (png_ptr == nullptr) {
            return nullptr;
        }
        
        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == nullptr)
        {
            png_destroy_read_struct(&png_ptr, NULL, NULL);
            return nullptr;
        }
        
        png_set_read_fn(png_ptr, (void *)&file, user_read_data_func);
        png_read_info(png_ptr, info_ptr);
        
        png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, 0, 0);
        
        if (color_type == PNG_COLOR_TYPE_PALETTE) {
            png_set_palette_to_rgb(png_ptr);
        }
        
        if (bit_depth < 8) {
            if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
                png_set_expand_gray_1_2_4_to_8(png_ptr);
            } else {
                png_set_packing(png_ptr);
            }
        }
        
        if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
            png_set_tRNS_to_alpha(png_ptr);
        }
        
        if (bit_depth == 16) {
            png_set_strip_16(png_ptr);
        }
        
        if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
            png_set_gray_to_rgb(png_ptr);
        }
        
        png_read_update_info(png_ptr, info_ptr);
        
        png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, 0, 0);
        
        if (color_type == PNG_COLOR_TYPE_RGB_ALPHA ||
            color_type == PNG_COLOR_TYPE_RGB) {
            png_set_bgr(png_ptr);
        }
        
        png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, 0, 0);
        
        enoImage* image = nullptr;
        u32 pitch = 0;
        
        if (color_type ==PNG_COLOR_TYPE_RGB_ALPHA) {
            image = new enoImage(GraphicsEnum::ColorFMT_BGRA8, core::size2d_template<u32>(width, height));
            pitch = 4*width;
        } else {
            image = new enoImage(GraphicsEnum::ColorFMT_BGR8, core::size2d_template<u32>(width, height));
            pitch = ((24*width+31)&~31)>>3;
        }
        
        u8 **buffer = new png_bytep[height];
        
        u8 *data = (u8 *)image->lock();
        data += (height-1)*pitch;
        
        for (u32 i = 0; i<height; i++) {
            buffer[i] = data;
            data -= pitch;
        }
        
        png_read_image(png_ptr, buffer);
        
        png_read_end(png_ptr, nullptr);
        delete [] buffer;
        image->unlock();
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        
        return image;
    }
    
}