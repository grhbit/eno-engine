/*
 *  ImageLoader_Bmp.cpp
 *  eno
 *
 *  Created by seonggwang.gwon on 11. 1. 26..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "ImageLoader_Bmp.hpp"
#include "enoFile.hpp"
#include "enoTimer.hpp"

namespace eno {

    struct BMPMagicNumber
    {
        u8 magicnumber[2];
        
        bool check(void)
        {
            return 
            (magicnumber[0]=='B') &&
            (magicnumber[1]=='M');
        }
    };

    struct BMPHeader
    {
    public:
        BMPHeader(void) : filesize(0),
            reserved1(0), reserved2(0), offset(0) { }

        union {
            u8 buffer[12];

            struct {
                u32 filesize;
                u16 reserved1;
                u16 reserved2;
                u32 offset;
            };
        };
    };

    struct DIBHeader
    {
    public:
        DIBHeader(void) : headersize(0), width(0), height(0),
            colorplane(0), colordepth(0), compressmethod(0),
            imagesize(0), width_pixelpermeter(0), height_pixelpermeter(0),
            colorpalettecount(0), importantcolorcount(0),
            redbitmask(0), greenbitmask(0), bluebitmask(0),
            alphabitmask(0) { }

        union {
            struct  
            {
                u32 headersize;
                s32 width;
                s32 height;
                u16 colorplane; // = 1
                u16 colordepth;
                u32 compressmethod;
                u32 imagesize;
                u32 width_pixelpermeter;
                u32 height_pixelpermeter;
                u32 colorpalettecount;
                u32 importantcolorcount; // ignored
                u32 redbitmask;
                u32 greenbitmask;
                u32 bluebitmask;
                u32 alphabitmask;
            };

            u8 buffer[56];
        };
    };

    void loadBitmapColorDepth1Bit(enoFile* file, enoImage** image, DIBHeader* info)
    {
        s32 width = info->width;
        s32 height = info->height;

        (*image) = new enoImage(GraphicsEnum::ColorFMT_RGBA8, core::size2d_template<u32>(width,height));
        u8*buffer = (*image)->lock();
        UNUSED(buffer);

        for (u32 i = 0; i<width*height; i++)
        {
        }

        (*image)->unlock();

    }

    void loadBitmapColorDepth8Bits(enoFile* file, enoImage** image, DIBHeader* info)
    {
        s32 width = info->width;
        s32 height = info->height;

        core::colorTypeI palette[256];

        for (s32 i = 0; i<256; i++) {
            file->readBytes(palette[i].v, sizeof(u32));
            palette[i].r = palette[i].r ^ palette[i].b;
            palette[i].b = palette[i].r ^ palette[i].b;
            palette[i].r = palette[i].r ^ palette[i].b;
            palette[i].a = 255;
        }

        (*image) = new enoImage(GraphicsEnum::ColorFMT_RGBA8, 
                                core::size2d_template<u32>(width, height));

        u8* buffer = (*image)->lock();
        u32*colorbuffer = 0;

        for (u32 i = 0; i<(width*height); i++)
        {
            colorbuffer = reinterpret_cast<u32*>(buffer);

            u8 index;
            file->readByte(&index);
            *colorbuffer = palette[index].color;
            std::cout << i << " " << (s32)palette[index].r << std::endl;

            buffer += 4;
        }

        (*image)->unlock();
    }

    u32 getBitsLength(u32 bits)
    {
        if(bits == 0) return 0;

        u32 ret = 0;
        while ((bits>>ret) != 0){ ++ret; }

        return ret;
    }

    u32 getShiftCount(u32 bits)
    {
        if(bits == 0) return 0;

        u32 ret = 0;
        while (((bits>>ret)%2) == 0) { ++ret; }

        return ret;
    }

    void loadBitmapColorDepth16Bits(enoFile* file, enoImage** image, DIBHeader* info)
    {
        s32 width = info->width;
        s32 height = info->height;

        (*image) = new enoImage(GraphicsEnum::ColorFMT_RGB5, core::size2d_template<u32>(width, abs(height)));

        u8* buffer = (*image)->lock();
        file->readBytes(buffer, info->imagesize);
        (*image)->unlock();
    }

    void loadBitmapColorDepth24Bits(enoFile* file, enoImage** image, DIBHeader* info)
    {
        s32 width = info->width;
        s32 height = info->height;

        (*image) = new enoImage(GraphicsEnum::ColorFMT_BGR8, core::size2d_template<u32>(width, abs(height)));

        u8* buffer = (*image)->lock();

        file->readBytes(buffer, info->imagesize);        
        (*image)->unlock();
    }

    void loadBitmapColorDepth32Bits(enoFile* file, enoImage** image, DIBHeader* info)
    {
        s32 width = info->width;
        s32 height = info->height;

        height = abs(height);
        (*image) = new enoImage(GraphicsEnum::ColorFMT_BGRX8, core::size2d_template<u32>(width, height));

        u8* buffer = (*image)->lock();
        file->readBytes(buffer, width*height*4);
        (*image)->unlock();
    }

    enoImage* ImageLoader_BMP::loadImage( const TextureID& ID )
    {
        enoFile file;
        file.open(ID.filename, enoFile::READ|enoFile::WRITE);
        
        if(!file.is_open()) {
            return nullptr;
        }

        BMPMagicNumber magicnumber;
        file.readByte(magicnumber.magicnumber+0);
        file.readByte(magicnumber.magicnumber+1);

        if (!magicnumber.check()) {
            return nullptr;
        }

        BMPHeader header;
        file.readBytes(header.buffer, sizeof(header));

        DIBHeader info;
        file.readBytes(info.buffer, sizeof(info.headersize));
        file.readBytes(info.buffer+sizeof(info.headersize),
                       info.headersize-sizeof(info.headersize));
        
        file.seekpos(header.offset);

        enoImage* image = nullptr;
        
        switch(info.colordepth)
        {
        case 1:
            loadBitmapColorDepth1Bit(&file, &image, &info);
            break;
        case 8:
            loadBitmapColorDepth8Bits(&file, &image, &info);
            break;
        case 16:
            loadBitmapColorDepth16Bits(&file, &image, &info);
            break;
        case 24:
            loadBitmapColorDepth24Bits(&file, &image, &info);
            break;
        case 32:
            loadBitmapColorDepth32Bits(&file, &image, &info);
            break;
        };

        file.close();
        return image;
    }

}