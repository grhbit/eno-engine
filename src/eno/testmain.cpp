/*
 *  testmain.cpp
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma warning(disable: 4819)
#include "enoConfig.h"

#ifdef ENO_WINDOWS_PLATFORM
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#endif

#include "enoType.h"
#include "matrix4x4.h"
#include <iostream>

#ifdef ENO_WINDOWS_PLATFORM
#include <d3d9.h>
#include <d3dx9.h>
#include "Core/DXUT.h"
#pragma  comment(lib, "d3dx9d.lib")
#pragma  comment(lib, "dxerr.lib")
#pragma comment(lib, "comctl32.lib")
#endif

using namespace std;

using namespace eno;
using namespace core;

bool enotypeTest();
bool enoMatrixMathTest();
bool enoVectorMathTest();

#ifdef ENO_MACOSX_PLATFORM
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#endif

#ifdef ENO_WINDOWS_PLATFORM
LPD3DXSPRITE SPRITE;
LPDIRECT3DTEXTURE9 TEX;

void Destroy( void* )
{
	SPRITE->Release();
}

void CALLBACK render(IDirect3DDevice9* device, f64, f32, void*)
{
	if (SUCCEEDED(device->BeginScene()))
	{
//		D3DXMATRIX mat;
//		D3DXMatrixScaling(&mat, 1, -1, 1);

//		SPRITE->SetTransform(&mat);
	if(SUCCEEDED(SPRITE->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		SPRITE->Draw(TEX,0,0,&D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(255,255,255));
	
		SPRITE->End();
	
	}

	device->EndScene();
	}
}
#endif


#include "TextureLoader_BMP.h"
#include "ITexture.h"

#ifdef ENO_WINDOWS_PLATFORM
void CALLBACK Lost(void*)
{
	SPRITE->OnLostDevice();
}

void CALLBACK Reset(IDirect3DDevice9* , const D3DSURFACE_DESC*, void*)
{
	SPRITE->OnResetDevice();
}
#endif

int main( int argc, char** argv )
{
//	display::CTexture_BMP bmp;
//	bmp.load("test.bmp", 0);

#ifdef ENO_WINDOWS_PLATFORM
	DXUTInit();
	DXUTSetCallbackD3D9FrameRender(render);
	DXUTCreateWindow();
	DXUTCreateDevice(true, 1024, 1024);

	IDirect3DDevice9* D9 = DXUTGetD3D9Device();
	D3DXCreateSprite(D9,&SPRITE);
#endif
	display::ITextureLoader* loader = new display::CTextureLoader_BMP;

	display::ITexture* tex = loader->load("test.bmp", 0);

#ifdef ENO_WINDOWS_PLATFORM
	D3DXCreateTexture(D9, tex->getWidth(), tex->getHeight(), 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &TEX);

	D3DLOCKED_RECT d3drt;
	TEX->LockRect(0, &d3drt, 0, 0);
	u8* bit = reinterpret_cast<u8*>(d3drt.pBits);

	memcpy(bit, tex->lock(), tex->getWidth()*tex->getHeight()*4);

	TEX->UnlockRect(0);
	tex->unlock();
#endif

	delete loader;

#ifdef ENO_WINDOWS_PLATFORM
	DXUTMainLoop();
#endif

	delete tex;

#ifdef ENO_WINDOWS_PLATFORM
	if(TEX) TEX->Release();

	if (SPRITE) SPRITE->Release();	
#endif
	{
		if(enotypeTest() == false)
			cout<<"enoTypeTest Failed."<<endl;

		if(enoMatrixMathTest() == false)
			cout<<"enoMatrixMathTest Failed."<<endl;

		if(enoVectorMathTest() == false)
			cout<<"enoVectorMathTest Failed."<<endl;
		
	}
	return 0;
}


bool enotypeTest()
{
	if (sizeof(eno::u8) != 1) {
		return false;
	}
	if (sizeof(eno::s8) != 1) {
		return false;
	}
	if (sizeof(eno::c8) != 1) {
		return false;
	}
	if (sizeof(eno::u16) != 2) {
		return false;
	}
	if (sizeof(eno::s16) != 2) {
		return false;
	}
	if (sizeof(eno::u32) != 4) {
		return false;
	}
	if (sizeof(eno::s32) != 4) {
		return false;
	}
	if (sizeof(eno::u64) != 8) {
		return false;
	}
	if (sizeof(eno::s64) != 8) {
		return false;
	}
	
	return true;
}

#include "vector3d.h"
#include "vector4d.h"

bool enoMatrixMathTest()
{
	return true;
}

bool enoVectorMathTest()
{
// 	D3DXVECTOR4 vec, lhs, mhs, rhs;
// 	vector4d Vec;
// 	vector4d Lhs( 2.0f, 1.0f, 3.0f, 1.0f );
// 	vector4d Mhs( 1.0f, 3.0f, 2.0f, 1.0f );
// 	vector4d Rhs( 1.0f, 3.0f, 10.0f, 1.0f );
// 
// 	lhs = D3DXVECTOR4(2.0f, 1.0f, 3.0f, 1.0f);
// 	mhs = D3DXVECTOR4(1.0f, 3.0f, 2.0f, 1.0f);
// 	rhs = D3DXVECTOR4(1.0f, 3.0f, 10.0f, 1.0f);
// 
// 	D3DXVec4Cross(&vec, &lhs, &mhs, &rhs);
// 	Vec.cross(Lhs, Mhs, Rhs);

	D3DXMATRIX Mat;
	D3DXQUATERNION Quat(1,4,2,1);

	quaternion_template<ftype> quat(1,4,2,1);

	matrix4x4 mat;

	matrix4x4::MakeRotateQuaternion(mat, quat);
	D3DXMatrixRotationQuaternion(&Mat, &Quat);

	return true;
}