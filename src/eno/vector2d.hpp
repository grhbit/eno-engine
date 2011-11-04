/*
 *  vector2d.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 22..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */


#pragma once
#include "enoType.h"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

#pragma warning(disable : 4201)	//warning: nonstandard extension used : nameless struct/union

			template<typename _Ty>
			struct
#ifdef ENO_COMPILED_FROM_VISUAL_STUDIO
ENO_ALIGNED(8)
#endif
			Vector2d {
			public:
				typedef _Ty element_type;
				typedef _Ty*pointer;
	
				union {
					struct {
						_Ty x, y;
					};
		
					_Ty v[2];
		
					u8 buffer[sizeof(_Ty) * 2];
				};
			}

#define Position2d Vector2d

#ifdef ENO_COMPILED_FROM_GNUC
ENO_ALIGNED(8)
#endif
;
#pragma warning(default : 4201)

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class vector2d_template : public struct_type::Vector2d<_Ty> {
			public:
				vector2d_template( void ) { }
				explicit vector2d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
				vector2d_template( _Ty _x, _Ty _y ) { this->x = _x; this->y = _y; }
				vector2d_template( const vector2d_template& vec ) { this->x = vec.x; this->y = vec.y; }

				inline vector2d_template& add( const vector2d_template& rhs )
				{
					vector2d_template::Add(*this, *this, rhs);
					return *this;
				}

				inline vector2d_template& add( const vector2d_template& lhs, const vector2d_template& rhs )
				{
					vector2d_template::Add(*this, lhs, rhs);
					return *this;
				}

				inline vector2d_template& subtract( const vector2d_template& rhs )
				{
					vector2d_template::Subtract(*this, *this, rhs);
					return *this;
				}

				inline vector2d_template& subtract( const vector2d_template& lhs, const vector2d_template& rhs )
				{
					vector2d_template::Subtract(*this, lhs, rhs);
					return *this;
				}

			//public static
			public:

				static inline void Add( vector2d_template& vec2, const vector2d_template& lhs, const vector2d_template& rhs )
				{
					vec2.x = lhs.x + rhs.x;
					vec2.y = lhs.y + rhs.y;
					vec2.z = lhs.z + rhs.z;
				}

				static inline vector2d_template Add( const vector2d_template& lhs, const vector2d_template& rhs )
				{
					vector2d_template tmp;
					vector2d_template::Add(tmp, lhs, rhs);
					return tmp;
				}

				static inline void Subtract( vector2d_template& vec2, const vector2d_template& lhs, const vector2d_template& rhs )
				{
					vec2.x = lhs.x - rhs.x;
					vec2.y = lhs.y - rhs.y;
					vec2.z = lhs.z - rhs.z;
				}

				static inline vector2d_template Subtract( const vector2d_template& lhs, const vector2d_template& rhs )
				{
					vector2d_template tmp;
					vector2d_template::Subtract(tmp, lhs, rhs);
					return tmp;
				}
			};

			typedef vector2d_template<ftype> vector2d;

#define position2d_template vector2d_template
#define position2d vector2d

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 1:31 pm Sunday. 8.22. 2010. Created.]
