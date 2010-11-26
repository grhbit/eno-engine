/*
 *  ITexture.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 27..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "IImage.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface ITexture : public IReferenceCounter
			{
			public:
			
				ITexture( void ) { }
			
				virtual ~ITexture( void ) { }

				virtual void init(size2d size, u8* data = 0) = 0;

				virtual u8* lock( u32 index = 0 ) = 0;

				virtual void unlock( u32 index = 0 ) = 0;

				virtual void bind( u8* buffer ) = 0;
				
				virtual IImage* getImage( u32 index = 0 ) const = 0;
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END

// 2:33