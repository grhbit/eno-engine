/*
*  D3DHelper_DX9.cpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 17..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#include "D3DHelper_DX9.hpp"

HRESULT D3DHelper_DX9::init(boolean windowed)
{
    d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

    if (d3d9 == nullptr)
        return E_FAIL;

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = windowed;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    if (FAILED(d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, NULL, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &device)))
        return E_FAIL;    
    
    return S_OK;
}
