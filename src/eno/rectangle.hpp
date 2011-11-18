/*
 *  rectangle.hpp
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
		ENO_STRUCT_TYPE_BEGIN

		template<typename _Ty>
		struct Rectangle {
		public:
			typedef _Ty element_type;
			typedef _Ty*pointer;
			
			union {
				struct {
					struct_type::Vector2d<_Ty> point1;
					struct_type::Vector2d<_Ty> point2;
				};
				
				struct {
					_Ty left, top, right, bottom;
				};
				
				_Ty r[4];
			};
		};

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class rectangle_template : public struct_type::Rectangle<_Ty> {
			public:
				rectangle_template( void ) { }
				
				explicit rectangle_template( const _Ty* src )
				{
					memcpy(this->r, src, sizeof(this->r));
				}
				
				_Ty getWidth( void ) const { return this->right - this->left; }
				
				_Ty getHeight( void ) const { return this->bottom - this->top; }
				
				_Ty getArea( void ) const { return getWidth() * getHeight(); }
				
				position2d_template<_Ty> getDimension2d( void ) const { return position2d_template<_Ty>(getWidth(), getHeight()); }
			};
	
		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END