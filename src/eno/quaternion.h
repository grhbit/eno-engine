/*
 *  quaternion.h
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
			Quaternion {
			public:
				typedef _Ty element_type;
				typedef _Ty*pointer;
	
				union {
					struct {
						_Ty x, y, z, w;
					};
		
					_Ty q[4];
		
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
			class quaternion_template : public struct_type::Quaternion<_Ty> {
			public:
				explicit quaternion_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
				quaternion_template( _Ty _x, _Ty _y, _Ty _z, _Ty _w ) { this->x = _x; this->y = _y; this->z = _z; this->w = _w; }
				quaternion_template( const quaternion_template& quat ) { this->x = quat.x; this->y = quat.y; this->z = quat.z; this->w = quat.w; }
			};

			typedef quaternion_template<ftype> quaternion;

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 1:43 pm Sunday. 8.22. 2010. Created.]
