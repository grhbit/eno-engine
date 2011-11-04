/*
 *  enoColor.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 11. 1. 25..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "eno.h"

ENO_NAMESPACE_BEGIN
	ENO_DISPLAY_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

#pragma warning(disable: 4201)

			class colorRGBA {
			public:
				explicit colorRGBA(u32 color):color(color) { }
				explicit colorRGBA(u8* color):r(color[0]), g(color[1]), b(color[2]), a(color[3]) { }
				colorRGBA(u8 r, u8 g, u8 b, u8 a):r(r), g(g), b(b), a(a) { }
				
				u32		getColor( void ) const { return color; }
				void	setColor( u32 color ) { this->color = color; }
				
				u32	getRedMask( void ) const { return 0xFF000000; }
				u32	getGreenMask( void ) const { return 0xFF0000; }
				u32	getBlueMask( void ) const { return 0xFF00; }
				u32	getAlphaMask( void ) const { return 0xFF; }
				
				u32		getRed( void ) const { return r; }
				void	setRed( u32 r ) { this->r = r; }
				
				u32		getGreen( void ) const { return g; }
				void	setGreen( u32 g ) { this->g = g; }
				
				u32		getBlue( void ) const { return b; }
				void	setBlue( u32 b ) { this->b = b; }
				
				u32		getAlpha( void ) const { return a; }
				void	setAlpha( u32 a ) { this->a = a; }
			private:
				union {
					struct {
						u8 r, g, b, a;						
					};

					u32 color;
				};
			};

#pragma warning(default : 4201)

			class colorfRGBA {
			public:
				explicit colorfRGBA(f32* color):r(color[0]), g(color[1]), b(color[2]), a(color[3]) { }
				colorfRGBA(f32 r, f32 g, f32 b, f32 a):r(r), g(g), b(b), a(a) { }
				
				f32		getRed( void ) const { return r; }
				void	setRed( f32 r ) { this->r = r; }
				
				f32		getGreen( void ) const { return g; }
				void	setGreen( f32 g ) { this->g = g; }
				
				f32		getBlue( void ) const { return b; }
				void	setBlue( f32 b ) { this->b = b; }
				
				f32		getAlpha( void ) const { return a; }
				void	setAlpha( f32 a ) { this->a = a; }
				
			private:
				f32 r, g, b, a;
			};

		typedef colorRGBA Color;

		typedef colorfRGBA VColor;

		ENO_CLASS_TYPE_END
	ENO_DISPLAY_NAMESPACE_END
ENO_NAMESPACE_END