/*
 *  Texture.h
 *  eno
 *
 *  Created by ±Ç¼º±¤ on 10. 8. 27..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "ITexture.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN
			
			class CTexture
				: public interface_type::ITexture
			{
			public:
				CTexture(void);
				virtual ~CTexture(void);
			};
			
		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END