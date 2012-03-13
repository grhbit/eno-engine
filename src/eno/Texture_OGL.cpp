/*
*  Texture_OGL.cpp
*  eno
*
*  Created by Gwon Seong-gwang on 11. 2. 24..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#include "Texture_OGL.hpp"
#include <GL/GL.h>
#include <GL/GLU.h>

namespace eno {

    void Texture_OGL::Init( core::size2d size, u8* data )
    {
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.getWidth(), size.getWidth(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    u8* Texture_OGL::Lock( u32 index )
    {
        // OpenGL not-support texture lock
        /*
        glBindTexture(GL_TEXTURE_2D, tex);
        glGetTexImage(GL_TEXTURE_2D, index, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
        */
        return nullptr;
    }

    void Texture_OGL::Unlock( u32 index )
    {
        // OpenGL not-support texture unlock-lock
    }

    void Texture_OGL::Bind( u8* buffer, u32 index )
    {
        /*
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexSubImage2D(GL_TEXTURE_2D, index, ...);
        glBindTexture(GL_TEXTURE_2D, 0);
        */
    }

    enoImage* Texture_OGL::GetImage( u32 index )
    {
        return nullptr;
    }
}