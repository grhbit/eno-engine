/*
*  enoDisplayType.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 9. 10..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include <list>
#include "enoType.hpp"
#include "vector2d.hpp"
#include "vector3d.hpp"
#include "colorType.hpp"
#include "rectangle.hpp"

namespace eno {

#define ENUM_INVALID_CHECK(Enum, value) ((Enum##_Count>value)&&(value>=0))
    
    enum BlendMode {
    };

    enum ColorFormat {
        ColorFMT_B1, //
        ColorFMT_P4,
        ColorFMT_P8,
        ColorFMT_RGB5,
        ColorFMT_R5G6B5,
        ColorFMT_RGB8,
        ColorFMT_RGBA8,
        ColorFMT_RGBA16,
        ColorFMT_RGBA32F,
        ColorFormat_Count,
    };

    enum CullMode {
        CULL_NONE,
        CULL_BACK,
        CULL_FRONT,
        CullMode_Count,
    };

    enum TextureMode
    {
        TextureMode_Count,
    };

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
            : p(0, 0, 0), n(0, 0, 0), c(1, 1, 1, 1), t(0, 0) { }

        spriteVertex(core::vector3d position, core::vector3d normal, core::colorTypeF color, core::vector2d texture)
            : p(position), n(normal), c(color), t(texture) { }

        core::vector3d p; // position
        core::vector3d n; // normal
        core::colorTypeF c; // diffuse color
        core::vector2d t; // texture coordinates
    };
    
    struct TextureID
    {
    public:
        boolean mipmap;
        CStdStringA filename;
        ColorFormat colorFormat;

    public:
        TextureID(void) : mipmap(false), filename(""), colorFormat(ColorFMT_RGBA8) {}
    };
}

//  [9/10/2010 6:52:35 Ultimate]