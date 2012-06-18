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
    
    struct DIBInfo
    {
    public:
        DIBInfo(void) : headersize(0), width(0), height(0),
        colorplane(0), colordepth(0), compressmethod(0),
        imagesize(0), width_pixelpermeter(0), height_pixelpermeter(0),
        colorpalettecount(0), importantcolorcount(0),
        redbitmask(0), greenbitmask(0), bluebitmask(0),
        alphabitmask(0) { }
        
        enum { BI_RGB = 0, BI_RLE8, BI_RLE4, BI_BITFIELDS, BI_JPEG, BI_PNG };
        enum { CORE = 12, INFO = 40, V2INFO = 52, V3INFO = 56, /* V4, V5, CORE2 */ };
        
        union {
            struct {
                u32 headersize;
                
                union {
                    struct {
                        s16 os_width;
                        s16 os_height;
                        s16 os_color_plane;
                        s16 os_color_depth;
                    };
                    
                    struct {
                        s32 width;
                        s32 height;
                    };
                };
                
                u16 colorplane; // = 1
                u16 colordepth; // OS/2 V1 12-byte
                u32 compressmethod;
                u32 imagesize;
                s32 width_pixelpermeter;
                s32 height_pixelpermeter;
                u32 colorpalettecount;
                u32 importantcolorcount; // Windows V1 40-byte
                u32 redbitmask;
                u32 greenbitmask;
                u32 bluebitmask;
                u32 alphabitmask;
            };
            
            u8 buffer[56];
        };
    };
    
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
    
    // BI_RGB
    void loadBitmapCompressedNone(enoFile& file, enoImage** image,
                                  BMPHeader& header, DIBInfo& info)
    {
        s32 numColors = 0;
        s32 width;
        s32 height;
        
        if (info.headersize == DIBInfo::CORE) {
            width = info.os_width;
            height = info.os_height;
            info.colordepth = info.os_color_depth;
            info.colorplane = info.os_color_plane;
        } else {
            width = info.width;
            height = info.height;
        }
        
        height = abs(height);
        
        if (!(numColors = info.colorpalettecount)) {
            if (info.colordepth <= 8) {
                numColors = 1 << info.colordepth;
            }
        }
        
        GraphicsEnum::ColorFormat format;
        
        switch (info.colordepth) {
            case 24:
                format = Graphics.ColorFMT_BGR8;
                break;
            case 1:
            case 4:
            case 8:
            case 32:
                format = info.headersize == DIBInfo::CORE?
                Graphics.ColorFMT_BGR8:Graphics.ColorFMT_BGRX8;
                break;
            case 16:
                format = Graphics.ColorFMT_X1BGR5;
                break;
            default:
                return;
        }
        
        if (info.colordepth > 8) {
            numColors = 0;
        }
        
        (*image) = new enoImage(format, 
                                core::size2d_template<u32>(width, height));
        
        // Palette
        if (numColors != 0) {
            file.seekpos(sizeof(BMPMagicNumber)+sizeof(header)+info.headersize);

            core::colorTypeI *palettes;
            palettes = new core::colorTypeI[numColors];

            const u32 colorsize = info.headersize == DIBInfo::CORE? 3:4;
            const u8 bitmask = (1<<info.colordepth)-1;
            const u8 loopcount = 8/info.colordepth;
            const s32 skipbytes = (4-(((((width*info.colordepth)%32)+7)&~7)>>3))%4;
            const s32 paddingbytes = ((width*colorsize+3)&~3)-(width*colorsize);

            for (s32 i = 0; i < numColors; i++) {
                file.readBytes(palettes[i].v, colorsize);
            }

            u8 index;
            file.seekpos(header.offset);
            u8 *buffer = (*image)->lock();
            for (s32 y = 0; y < height; y++) {
                for (s32 x = 0; x < width;) {
                    file.readByte(&index);
                    for (s32 c = loopcount-1; (c >= 0) && (x < width); c--, x++) {
                        memcpy(buffer, palettes[(index>>(c*info.colordepth))&bitmask].v, colorsize);
                        buffer += colorsize;
                    }
                }
                file.seekcur(skipbytes);
                buffer += paddingbytes;
            }

            (*image)->unlock();
            delete [] palettes;
        } else {
            s32 stride = ((width*info.colordepth+31)&~31)>>3;
            file.seekpos(header.offset);
            
            u8 *buffer = (*image)->lock();
            file.readBytes(buffer, stride*height);
            (*image)->unlock();
        }
    }
    
    // BI_BITFIELDS
    void loadBitmapCompressedBitfields(enoFile& file, enoImage** image,
                                       BMPHeader& header, DIBInfo& info)
    {
        if ((info.colordepth != 16) && (info.colordepth != 32)) {
            return;
        }

        GraphicsEnum::ColorFormat format;
        if (info.alphabitmask == 0) {
            if (info.colordepth == 16) {
                format = Graphics.ColorFMT_X1BGR5;
            } else {
                format = Graphics.ColorFMT_BGRX8;
            }
        } else {
            if (info.colordepth == 16) {
                format = Graphics.ColorFMT_A1BGR5;
            } else {
                format = Graphics.ColorFMT_BGRA8;
            }
        }
        
    }
    
    enoImage* ImageLoader_BMP::loadImage( const TextureID& ID )
    {
        enoFile file;
        file.open(ID.filename, enoFile::READ);
        
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

        DIBInfo info;
        file.readBytes(info.buffer, sizeof(info.headersize));
        file.seekpos(sizeof(magicnumber)+sizeof(header));
        file.readBytes(info.buffer, info.headersize < sizeof(info)?
                       info.headersize:sizeof(info));

        enoImage* image = nullptr;
        
        switch (info.compressmethod) {
            case DIBInfo::BI_RGB:
                loadBitmapCompressedNone(file, &image, header, info);
                break;
            case DIBInfo::BI_BITFIELDS:
                loadBitmapCompressedBitfields(file, &image, header, info);
                break;
            case DIBInfo::BI_RLE8:
            case DIBInfo::BI_RLE4:
            case DIBInfo::BI_JPEG:
            case DIBInfo::BI_PNG:
                break;
        };

        file.close();
        return image;
    }
    



}