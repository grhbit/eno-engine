/*
 *  ITexture.h
 *  eno
 *
 *  Created by ±Ç¼º±¤ on 10. 8. 27..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "IReferenceCounter.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface ITexture
			: public IReferenceCounter
			{
			public:
			
				ITexture( void ) { }
			
				virtual ~ITexture( void ) { }

				virtual void init(u32 width, u32 height, bool bUsedResourceManagement = true, u8* data = 0) = 0;

				virtual u8* lock( void ) = 0;

				virtual void unlock( void ) = 0;

				virtual void bind( u8* buffer ) = 0;
			
				virtual u32 getWidth( void ) const = 0;

				virtual u32 getHeight( void ) const = 0;

				virtual void setWidth( u32 width ) = 0;

				virtual void setHeight( u32 height ) = 0;
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

// 2:33