/*
*  GraphicsImpl_DX.cpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 17..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#include "GraphicsImpl_DX.hpp"
#include "D3DHelper_DX9.hpp"

namespace eno
{
#define D3DHelper(n) D3DHelper_DX##n

    void GraphicsImpl_DX::create(GraphicsMode mode)
    {
        D3DHelper(9) helper;
    }

}