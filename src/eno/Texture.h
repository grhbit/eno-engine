/*
 *  Texture.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 27..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoTexture.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN
			
			class CTexture
				: public interface_type::enoTexture
			{
			public:
				CTexture(void) { this->data = 0; }
				
				/* virtual */ ~CTexture(void) { if (this->data) delete [](this->data); }

			protected:
				/* virtual */ void init(u32 width, u32 height, bool bUsedResourceManagement = true, u8* data = 0) { this->width = width; this->height = height; }

				/* virtual */ u8* lock( void ) { return this->data; }

				/* virtual */ void unlock( void ) { /* nothing */ }

				/* virtual */ void bind( u8* buf ) { data = buf; }

				/* virtual */ u32 getWidth() const { return width; }

				/* virtual */ u32 getHeight() const { return height; }

				/* virtual */ void setWidth( u32 w ) { width = w; }

				/* virtual */ void setHeight( u32 h ) { height = h; }

			private:
				u8* data;

				u32 width, height;
			};
			
		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END