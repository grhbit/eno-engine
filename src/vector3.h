/*
 *  vector3.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 14..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "enoType.h"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

			template<typename _Ty>
			struct Vector3 {
				union {
					struct {
						_Ty x, y, z;
					};
					
					_Ty v[3];
				};
			};

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class vector3_template : public struct_type::Vector3<_Ty> {
			public:
				explicit vector3_template( _Ty* src ) { memcpy( this->v, src ); }
				explicit vector3_template( _Ty _x, _Ty _y, _Ty _z ) { this->x; this->y; this->z; }
				explicit vector3_template( const vector3_template& vec ) { this->x = vec.x; this->y = vec.y; this->z = vec.z; }
			};

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// [skop 4:24 pm Saturday. 8.14. 2010. Created.]

