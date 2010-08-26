/*
 *  Texture_BMP.h
 *  eno
 *
 *  Created by ±Ç¼º±¤ on 10. 8. 27..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "Texture.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN
			
			class CTexture_BMP
				: public CTexture
			{
			public:
				CTexture_BMP(void);
				~CTexture_BMP(void);

				void load(char* path, u8* );
			};
			
		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END