/*
 *  IImage.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 11. 23..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "IReferenceCounter.h"
#include "dimension2d.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface IImage : public IReferenceCounter
			{
			public:
				
				IImage( void ) { }
				
				virtual ~IImage( void ) { }
				
				virtual u8* lock( void ) = 0;
				
				virtual void unlock( void ) = 0;
				
				virtual void bind( u8* buffer ) = 0;

				virtual core::class_type::size2d_template<u32> getSize( void ) const = 0;
				
				virtual u32 getWidth( void ) const = 0;
				
				virtual u32 getHeight( void ) const = 0;
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END