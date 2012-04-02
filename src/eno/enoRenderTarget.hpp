//
//  enoRenderTarget.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 3..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoTexture.hpp"

namespace eno {
    

interface enoRenderTarget
{
public:
    virtual void BeginRenderTargetTexture(void) = 0;

    virtual void EndRenderTargetTexture(void) = 0;
};


    }
