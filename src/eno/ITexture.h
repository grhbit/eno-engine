/*
 *  ITexture.h
 *  eno
 *
 *  Created by ±Ç¼º±¤ on 10. 8. 27..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "enoType.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface ITexture
			{
			public:
			
				ITexture( void ) { }
			
				virtual ~ITexture( void ) { }

				virtual u8* lock( void ) = 0;

				virtual void unlock( void ) = 0;
			
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

// 2:33