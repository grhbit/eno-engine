/*
*  D3DHelper_DX9.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 12. 2. 17..
*  Copyright 2012 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "enoType.hpp"

#if defined(ENO_DISPLAY_DIRECT_9)
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")

#if defined(NDEBUG)
#pragma comment(lib, "d3dx9.lib")
#elif defined(DEBUG)
#pragma comment(lib, "d3dx9d.lib")
#endif

class D3DHelper_DX9
{
public:
    D3DHelper_DX9(void) : d3d9(nullptr), device(nullptr) {}

    HRESULT init(boolean windowed);
private:
    IDirect3D9* d3d9;
    IDirect3DDevice9* device;
    D3DPRESENT_PARAMETERS d3dpp;
};

#endif