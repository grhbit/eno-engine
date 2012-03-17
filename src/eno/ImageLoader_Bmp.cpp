/*
 *  ImageLoader_Bmp.cpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 11. 1. 26..
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
                u32 width;
                u32 height;
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

    void loadBitmapColorDepth1Bit(enoFile* file, enoImage* image, DIBHeader* info)
    {
        u32 width = info->width;
        u32 height = info->height;

        u8* buffer = new u8[width*height*4];

        image->bind(buffer);

        for (u32 i = 0; i<width*height; i++)
        {
        }

        image->setSize(core::size2d_template<u32>(width, height));
    }

    void loadBitmapColorDepth8Bits(enoFile* file, enoImage* image, DIBHeader* info)
    {
        u32 width = info->width;
        u32 height = info->height;

        core::colorTypeI palette[256];

        for (s32 i = 0; i<256; i++) {
            file->getBytes(palette[i].v, sizeof(u32));
            palette[i].r = palette[i].r ^ palette[i].b;
            palette[i].b = palette[i].r ^ palette[i].b;
            palette[i].r = palette[i].r ^ palette[i].b;
            palette[i].a = 255;
        }

        u8* buffer = new u8[width*height*4];
        u32*colorbuffer = 0;

        image->bind(buffer);

        for (u32 i = 0; i<(width*height); i++)
        {
            colorbuffer = reinterpret_cast<u32*>(buffer);

            u8 index = file->getByte();
            *colorbuffer = palette[index].color;
            std::cout << i << " " << (s32)palette[index].r << std::endl;

            buffer += 4;
        }
        
        image->setSize(core::size2d_template<u32>(width, height));
        image->setColorFormat(ColorFMT_RGBA8);
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

    void loadBitmapColorDepth16Bits(enoFile* file, enoImage* image, DIBHeader* info)
    {
        u32 width = info->width;
        u32 height = info->height;

        struct {
            union {

                u8 buffer[2];
                u16 color;
            };
        } bits;

        u8* buffer = new u8[width * height * 4];
        u32*colorbuffer = 0;

        u32 redShift = getShiftCount(info->redbitmask);
        u32 redMask = info->redbitmask >> redShift;
        u32 redLength = getBitsLength(redMask);

        u32 greenShift = getShiftCount(info->greenbitmask);
        u32 greenMask = info->greenbitmask >> greenShift;
        u32 greenLength = getBitsLength(greenMask);

        u32 blueShift = getShiftCount(info->bluebitmask);
        u32 blueMask = info->bluebitmask >> blueShift;
        u32 blueLength = getBitsLength(blueMask);

        image->bind(buffer);

        enoTimer timer;
        core::colorTypeI color;

        for (u32 y = 0; y < height; y++)
        {
            for (u32 x = 0; x < width; x++)
            {
                colorbuffer = reinterpret_cast<u32*>(buffer);

                file->getBytes(bits.buffer, sizeof(u8)*2);

                color.r = ((bits.color>>redShift)&redMask)<<(8-redLength);
                color.g = ((bits.color>>greenShift)&greenMask)<<(8-greenLength);
                color.b = ((bits.color>>blueShift)&blueMask)<<(8-blueLength);
                color.a = 255;

                *colorbuffer = color.color;

                buffer += 4;
            }
        }

        image->setSize(core::size2d_template<u32>(width, height));

        std::cout << timer.touch() << std::endl;
    }

    void loadBitmapColorDepth24Bits(enoFile* file, enoImage* image, DIBHeader* info)
    {
        u32 width = info->width;
        u32 height = info->height;

        struct {
            union {
                struct {
                    u8 r;
                    u8 g;
                    u8 b;
                };

                u8 buffer[3];
            };
        } bits;

        u8* buffer = new u8[width * height * 3];
        u32*colorbuffer = 0;

        image->bind(buffer);

        enoTimer timer;

        for (u32 y = 0; y < height; y++)
        {
            for (u32 x = 0; x < width; x++)
            {
                colorbuffer = reinterpret_cast<u32*>(buffer);

                file->getBytes(bits.buffer, sizeof(u8)*3);

                bits.r = bits.r^bits.b;
                bits.b = bits.r^bits.b;
                bits.r = bits.r^bits.b;

                memcpy(colorbuffer, bits.buffer, sizeof(u8)*3);

                buffer += 3;
            }
        }

        image->setSize(core::size2d_template<u32>(width, height));
        image->setColorFormat(ColorFMT_RGB8);

        std::cout << timer.touch() << std::endl;
    }

    void loadBitmapColorDepth32Bits(enoFile* file, enoImage* image, DIBHeader* info)
    {
        u32 width = info->width;
        u32 height = info->height;

        struct {
            union {
                struct {
                    u8 r;
                    u8 g;
                    u8 b;
                    u8 a;
                };

                u8 buffer[4];
                u32 color;
            };
        } bits;

        u8* buffer = new u8[width * height * 4];
        u32*colorbuffer = 0;

        image->bind(buffer);

        enoTimer timer;

        for (u32 y = 0; y < height; y++)
        {
            for (u32 x = 0; x < width; x++)
            {
                colorbuffer = reinterpret_cast<u32*>(buffer);

                file->getBytes(bits.buffer, sizeof(u32));

                bits.color = bits.color>>8;
                bits.r = bits.r^bits.b;
                bits.b = bits.r^bits.b;
                bits.r = bits.r^bits.b;
                bits.a = 255;

                *colorbuffer = bits.color;

                buffer += 4;
            }
        }

        image->setSize(core::size2d_template<u32>(width, height));
        image->setColorFormat(ColorFMT_RGBA8);

        std::cout << timer.touch() << std::endl;        
    }

    enoImage* ImageLoader_BMP::loadImage( const TextureID& ID )
    {
        enoFile file;
        file.open(ID.filename, enoFile::READ|enoFile::BINARY);
        file.seek(0);

        BMPMagicNumber magicnumber;
        magicnumber.magicnumber[0] = file.getByte();
        magicnumber.magicnumber[1] = file.getByte();

        BMPHeader header;
        file.getBytes(header.buffer, sizeof(BMPHeader));

        DIBHeader info;
        file.getBytes(info.buffer, sizeof(info.headersize));
        file.getBytes(info.buffer+4, info.headersize-sizeof(info.headersize));

        enoImage* image = new enoImage;

        switch(info.colordepth)
        {
        case 1:
            loadBitmapColorDepth1Bit(&file, image, &info);
            break;
        case 8:
            loadBitmapColorDepth8Bits(&file, image, &info);
            break;
        case 16:
            loadBitmapColorDepth16Bits(&file, image, &info);
            break;
        case 24:
            loadBitmapColorDepth24Bits(&file, image, &info);
            break;
        case 32:
            loadBitmapColorDepth32Bits(&file, image, &info);
            break;
        };

        file.close();
        return image;
    }

}