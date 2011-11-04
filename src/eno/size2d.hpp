/*
 *  size2d.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 11. 23..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "vector2d.hpp"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class size2d_template : public struct_type::Vector2d<_Ty> {
			public:
				size2d_template( void ) { }
				explicit size2d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
				size2d_template( _Ty width, _Ty height ) { this->x = width; this->y = height; }
				size2d_template( const size2d_template& size ) { this->x = size.x; this->y = size.y; }
				
				_Ty getWidth( void ) const { return this->x; }
				_Ty getHeight( void ) const { return this->y; }
			};

			typedef size2d_template<ftype> size2d;

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END