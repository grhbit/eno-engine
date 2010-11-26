/*
 *  dimension2d.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 11. 23..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "vector2d.h"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class dimension2d_template : public struct_type::Vector2d<_Ty> {
			public:
				dimension2d_template( void ) { }
				explicit dimension2d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
				dimension2d_template( _Ty width, _Ty height ) { this->x = width; this->y = height; }
				dimension2d_template( const dimension2d_template& dim ) { this->x = dim.x; this->y = dim.y; }
				
				_Ty getWidth( void ) const { return this->x; }
				_Ty getHeight( void ) const { return this->y; }
			};

			typedef dimension2d_template<ftype> dimension2d;

#define size2d_template dimension2d_template
#define size2d dimension2d

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END