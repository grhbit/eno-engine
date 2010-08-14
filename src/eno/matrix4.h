/*
 *  matrix4.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "enoType.h"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN
#pragma pack(push,16)
			template<typename _Ty>
			struct Matrix4x4 {
			public:
				union {
					struct {
						_Ty _11, _12, _13, _14;
						_Ty _21, _22, _23, _24;
						_Ty _31, _32, _33, _34;
						_Ty _41, _42, _43, _44;
					};
					
					_Ty m[4][4];
					_Ty M[16];
				};
			};
#pragma pack(pop)

		ENO_STRUCT_TYPE_END

		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class matrix4x4 : public struct_type::Matrix4x4<_Ty> {
			public:
				explicit matrix4x4( void ) { }
				explicit matrix4x4( _Ty* src ) { memcpy(this->M, src, sizeof(this->M));}
				explicit matrix4x4( _Ty _11, _Ty _12, _Ty _13, _Ty _14,
								    _Ty _21, _Ty _22, _Ty _23, _Ty _24,
								    _Ty _31, _Ty _32, _Ty _33, _Ty _34,
								    _Ty _41, _Ty _42, _Ty _43, _Ty _44 )
				{
					this->m[0][0];
				}
												   
				
				
			};

			typedef matrix4x4<f32> matrix4;

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// 12 :46 Friday 13 8 2010.

