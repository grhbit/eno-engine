/*
 *  vector2d.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 22..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */


#pragma once
#include "enoType.h"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

			template<typename _Ty>
			struct
#ifdef ENO_COMPILED_FROM_VISUAL_STUDIO
ENO_ALIGNED_16
#endif
			Vector2d {
			public:
				typedef _Ty element_type;
				typedef _Ty*pointer;
	
				union {
					struct {
						_Ty x, y, z;
					};
		
					_Ty v[3];
		
					u8 buffer[sizeof(_Ty) * 12];
				};
			}
#ifdef ENO_COMPILED_FROM_GNUC
ENO_ALIGNED_16
#endif
;

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class vector2d_template : public struct_type::Vector2d<_Ty> {
			public:
				explicit vector2d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
				vector2d_template( _Ty _x, _Ty _y ) { this->x = _x; this->y = _y; }
				vector2d_template( const vector2d_template& vec ) { this->x = vec.x; this->y = vec.y; }
			};

			typedef vector2d_template<ftype> vector2d;

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 1:31 pm Sunday. 8.22. 2010. Created.]
