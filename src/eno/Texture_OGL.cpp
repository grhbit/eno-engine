/*
*  Texture_OGL.cpp
*  eno
*
*  Created by Gwon Seong-gwang on 11. 2. 24..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#include "Texture_OGL.hpp"
#include "GraphicsImpl_OGL.hpp"

namespace eno {
    
    Texture_OGL::Texture_OGL() : image(nullptr), tex(0)
    {
    }
    
    Texture_OGL::~Texture_OGL() { glDeleteTextures(1, &tex); }

    void Texture_OGL::Init( core::size2d_template<u32> size, GraphicsEnum::ColorFormat format,
                           u8* data )
    {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        if (data != nullptr) {
            glTexImage2D(GL_TEXTURE_2D, 0,
                         std::get<OpenGLEnum::INTERNAL_FORMAT>(OpenGL.TextureInfo[format]),
                         size.getWidth(), size.getHeight(), 0,
                         std::get<OpenGLEnum::FORMAT>(OpenGL.TextureInfo[format]),
                         std::get<OpenGLEnum::TYPE>(OpenGL.TextureInfo[format]),
                         data);
        }

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    u8* Texture_OGL::Lock( u32 index )
    {
        // OpenGL not-support(not necessary) texture lock
        
        glBindTexture(GL_TEXTURE_2D, tex);
        glBindTexture(GL_TEXTURE_2D, 0);

        return nullptr;
    }

    void Texture_OGL::Unlock( u32 index )
    {
        // OpenGL not-support(not necessary) texture unlock-lock
        UNUSED(index);
    }

    void Texture_OGL::Bind( u8* buffer, u32 index )
    {
        /*
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexSubImage2D(GL_TEXTURE_2D, index, ...);
        glBindTexture(GL_TEXTURE_2D, 0);
        */
    }

    enoImage* Texture_OGL::GetImage( u32 index ) const
    {
        return nullptr;
    }
    
    u32 Texture_OGL::GetTexture() const
    {
        return tex;
    }
}