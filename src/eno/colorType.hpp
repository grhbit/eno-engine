//
//  colorTypeF.cpp
//  eno
//
//  Created by seonggwang.gwon on 12. 1. 20..
//  Copyright (c) 2012 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoType.hpp"
#include "enoMath.hpp"

namespace eno {
    namespace core {

        struct ColorTypeF
        {
        public:
            union {
                struct {
                    f32 r; // red
                    f32 g; // green
                    f32 b; // blue
                    f32 a; // alpha
                };

                f32 v[4];
            };

            ColorTypeF( void ) : a(1), r(0), g(0), b(0) { }

            ColorTypeF(f32 red, f32 green, f32 blue, f32 alpha)
                : r(red), g(green), b(blue), a(alpha) { }

            ColorTypeF(f32* value)
            {
                memcpy(v, value, sizeof(v));
            }
        };

        class colorTypeF : public ColorTypeF
        {
        public:
            colorTypeF( void ) : ColorTypeF() { }

            colorTypeF(f32 red, f32 green, f32 blue, f32 alpha)
                : ColorTypeF(red, green, blue, alpha) { }

            colorTypeF(f32* value) : ColorTypeF(value) { }

            f32 getAlpha() const { return a; }
            f32 getRed() const { return r; }
            f32 getGreen() const { return g; }
            f32 getBlue() const { return b; }

            u32 getColorCode() const
            {
                return (static_cast<u8>(r*255)<<24) |
                    (static_cast<u8>(g*255)<<16) |
                    (static_cast<u8>(b*255)<<8) |
                    (static_cast<u8>(a*255));
            }

            /* void setHSL Info.
            *      value : range
            *        hue : [0, 2*PI]
            * saturation : [0, 1]
            *  lightness : [0, 1]
            */
            void setHSL(f32& h, f32& s, f32& l)
            {
                while(h>2.0*PI) h -= 2.0*PI;
                while(h<0.0) h += 2.0*PI;
                while(s>1.0) s -= 1.0;
                while(s<0.0) s += 1.0;
                while(l>1.0) l -= 1.0;
                while(l<0.0) l += 1.0;

                f32 chroma = (1 - abs(2.f*l - 1)) * s;
                f32 h_prime = h*(3/PI);
                f32 X = chroma*(1 - abs(fmodf(h_prime, 2) - 1));
                f32 m = l - chroma*0.5f;

                switch(static_cast<s32>(h_prime))
                {
                case 0:
                    r = chroma; g = X; b = 0;
                    break;
                case 1:
                    r = X; g = chroma; b = 0;
                    break;
                case 2:
                    r = 0; g = chroma; b = X;
                    break;
                case 3:
                    r = 0; g = X; b = chroma;
                    break;
                case 4:
                    r = X; g = 0; b = chroma;
                    break;
                case 5:
                    r = chroma; g = 0; b = X;
                    break;
                };

                r += m;
                g += m;
                b += m;
            }

        public:
            static colorTypeF GetHSL(f32 hue, f32 saturation, f32 lightness)
            {
                colorTypeF tmp;
                tmp.setHSL(hue, saturation, lightness);
                return tmp;
            }

        };

        struct ColorTypeI
        {
        public:
            union {
                struct {
                    u8 r; // red
                    u8 g; // green
                    u8 b; // blue
                    u8 a; // alpha
                };

                u8 v[4];
                u32 color;
            };

            ColorTypeI( void ) : a(0xFF), r(0), g(0), b(0) { }

            ColorTypeI(u8 alpha, u8 red, u8 green, u8 blue)
                : a(alpha), r(red), g(green), b(blue) { }

            ColorTypeI(u32 colour) : color(colour) { }

            ColorTypeI(u8* value)
            {
                memcpy(v, value, sizeof(v));
            }
        };

        class colorTypeI : public ColorTypeI
        {
        public:
            colorTypeI( void ) : ColorTypeI() { }

            colorTypeI(u8 alpha, u8 red, u8 green, u8 blue)
                : ColorTypeI(alpha, red, green, blue) { }

            colorTypeI(u32 colour) : ColorTypeI(colour) { }

            colorTypeI(u8* value) : ColorTypeI(value) { }

            u8 getAlpha() const { return a; }
            u8 getRed() const { return r; }
            u8 getGreen() const { return g; }
            u8 getBlue() const { return b; }

            u32 getColorCode() const
            {
                return color;
            }

            u32 getAlphaMask() const { return 0xff000000; }
            u32 getRedMask() const { return   0x00ff0000; }
            u32 getGreenMask() const { return 0x0000ff00; }
            u32 getBlueMask() const { return  0x000000ff; }

        };

    }
}