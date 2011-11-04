/*
 *  enoImage.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 11. 23..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoReferenceCounter.hpp"
#include "enoDisplay.h"
#include "enoDisplayType.h"
#include "size2d.hpp"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_INTERFACE_TYPE_BEGIN

			interface enoImage : public enoReferenceCounter
			{
			public:
				
				enoImage( void ) { }
				
				virtual ~enoImage( void ) { }
				
				u8* lock( void ) { return Lock(); }
				
				void unlock( void ) { return Unlock(); }
				
				void bind( u8* buffer ) { return Bind(buffer); }

				core::class_type::size2d_template<u32> getSize( void ) const { return GetSize(); }
				
				u32 getWidth( void ) const { return GetWidth(); }
				
				u32 getHeight( void ) const { return GetHeight(); }
				
				void setPixel( enum_type::EColorFormat fmt,
							  class_type::Color color, 
							  core::class_type::position2d_template<u32> pos ) { SetPixel(fmt, color, pos); }
				
				enum_type::EColorFormat getColorFormat( void ) const { return GetColorFormat(); }

			protected:
				virtual u8* Lock( void ) = 0;
				
				virtual void Unlock( void ) = 0;
				
				virtual void Bind( u8* buffer ) = 0;
				
				virtual core::class_type::size2d_template<u32> GetSize( void ) const = 0;
				
				virtual u32 GetWidth( void ) const = 0;
				
				virtual u32 GetHeight( void ) const = 0;
				
				virtual void SetPixel( enum_type::EColorFormat,
									  class_type::Color,
									  core::class_type::position2d_template<u32> ) = 0;
				
				virtual enum_type::EColorFormat GetColorFormat( void ) const = 0;
			};

		ENO_INTERFACE_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END