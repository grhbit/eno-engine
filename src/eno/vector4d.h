/*
 *  vector4d.h
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
			Vector4d {
			public:
				typedef _Ty element_type;
				typedef _Ty*pointer;
	
				union {
					struct {
						_Ty x, y, z, w;
					};
		
					_Ty v[4];
		
					u8 buffer[sizeof(_Ty) * 4];
				};
			}
#ifdef ENO_COMPILED_FROM_GNUC
ENO_ALIGNED_16
#endif
;

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class vector4d_template : public struct_type::Vector4d<_Ty> {
			public:
				explicit vector4d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
				vector4d_template( _Ty _x, _Ty _y, _Ty _z, _Ty _w ) { this->x = _x; this->y = _y; this->z = _z; this->w = _w; }
				vector4d_template( const vector4d_template& vec ) { this->x = vec.x; this->y = vec.y; this->z = vec.z; this->w = vec.w; }
			};

			typedef vector4d_template<ftype> vector4d;

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 1:21 pm Sunday. 8.22. 2010. Created.]
