/*
*  enoDisplayType.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 9. 10..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include <tuple>
#include <list>

#include "enoType.hpp"
#include "vector2d.hpp"
#include "vector3d.hpp"
#include "colorType.hpp"
#include "rectangle.hpp"

namespace eno {

#define ENUM_INVALID_CHECK(Enum, value) ((Enum##_Count>value)&&(value>=0))
    
    static const struct GraphicsEnum
    {
    public:
        enum BlendMode {
        };

        enum CullMode {
            CULL_NONE = 0,
            CULL_BACK = 1,
            CULL_FRONT = 2,
            CullMode_Count = 3
        };

        enum ColorFormat {
            // --- No alpha channel
            ColorFMT_RGB5 = 0,
            ColorFMT_RGB8,
            ColorFMT_BGR8,
            ColorFMT_BGRX8,
            
            // --- Alpha channel
            ColorFMT_RGBA4,
            ColorFMT_RGB5A1,
            ColorFMT_A1BGR5,
            ColorFMT_RGBA8,
            ColorFMT_BGRA8,
            ColorFormat_Count
        };

        enum { DEPTH, ALPHA };

        typedef std::tuple<int, bool> COLORFORMAT_INFO;
        COLORFORMAT_INFO ColorFormatInfo[ColorFormat_Count];

        enum TextureMode {
            TextureMode_Count
        };
            
        GraphicsEnum();
    } Graphics;

    class matrixStack
    {
    public:
        matrixStack(void) {}

        void push(void) { stack.push_back(core::matrix4x4()); }
        void pop(void) { stack.pop_back(); }

        void mult(const core::matrix4x4& mat) { stack.back().multiply(mat); }
        void multLocal(const core::matrix4x4& mat) { stack.back().multiplyLocal(mat); }

        void scale(const core::vector3d& vec3) { stack.back().multiply(core::matrix4x4::MakeScale(vec3)); }
        void rotate(const core::vector3d& vec3) { stack.back().multiply(core::matrix4x4::MakeRotate(vec3)); }
        void translate(const core::vector3d& vec3) { stack.back().multiply(core::matrix4x4::MakeTranslate(vec3)); }

    private:
        std::list<core::matrix4x4> stack;
    };

    class spriteVertex
    {
    public:
        spriteVertex( void )
            : p(0, 0, 0), c(1, 1, 1, 1), t(0, 0) { }

        spriteVertex(core::vector3d position, core::colorTypeF color, core::vector2d texture)
            : p(position), c(color), t(texture) { }

        core::vector3d p; // position
        core::colorTypeF c; // diffuse color
        core::vector2d t; // texture coordinates
    };
    
    class modelVertex : public spriteVertex
    {
    public:
        modelVertex(core::vector3d position, core::colorTypeF color, core::vector2d texture, core::vector4d normal)
        : spriteVertex(position, color, texture), n(normal) { }

        modelVertex( void )
            : n(0, 0, 0, 0) { }
        
        core::vector4d n;
    };
    
    struct TextureID
    {
    public:
        bool mipmap;
        RString filename;

    public:
        TextureID(void) : mipmap(false), filename("") {}
    };
}

//  [9/10/2010 6:52:35 Ultimate]