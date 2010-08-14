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
#include "vector3.h"

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
				#define m11 m[0][0]
				#define m12 m[0][1]
				#define m13 m[0][2]
				#define m14 m[0][3]
				#define m21 m[1][0]
				#define m22 m[1][1]
				#define m23 m[1][2]
				#define m24 m[1][3]
				#define m31 m[2][0]
				#define m32 m[2][1]
				#define m33 m[2][2]
				#define m34 m[2][3]
				#define m41 m[3][0]
				#define m42 m[3][1]
				#define m43 m[3][2]
				#define m44 m[3][3]

				enum InitializeFlag {
					INIT_NOTHING,
					INIT_IDENTITY,
					INIT_ZERO,
					INIT_FILL
				};
			public:
				explicit matrix4x4( _Ty* src ) { memcpy(this->M, src, sizeof(this->M));}
				explicit matrix4x4( _Ty _11, _Ty _12, _Ty _13, _Ty _14,
								    _Ty _21, _Ty _22, _Ty _23, _Ty _24,
								    _Ty _31, _Ty _32, _Ty _33, _Ty _34,
								    _Ty _41, _Ty _42, _Ty _43, _Ty _44 )
				{
					this->m11 = _11;	this->m12 = _12;	this->m13 = _13;	this->m14 = _14;
					this->m21 = _21;	this->m22 = _22;	this->m23 = _23;	this->m24 = _24;
					this->m31 = _31;	this->m32 = _32;	this->m33 = _33;	this->m34 = _34;
					this->m41 = _41;	this->m42 = _42;	this->m43 = _43;	this->m44 = _44;
				}
				
				explicit matrix4x4( const matrix4x4& rhs )
				{
					this->m11 = rhs.m11;	this->m12 = rhs.m12;	this->m13 = rhs.m13;	this->m14 = rhs.m14;
					this->m21 = rhs.m21;	this->m22 = rhs.m22;	this->m23 = rhs.m23;	this->m24 = rhs.m24;
					this->m31 = rhs.m31;	this->m32 = rhs.m32;	this->m33 = rhs.m33;	this->m34 = rhs.m34;
					this->m41 = rhs.m41;	this->m42 = rhs.m42;	this->m43 = rhs.m43;	this->m44 = rhs.m44;					
				}

				explicit matrix4x4( InitializeFlag initFlag = INIT_IDENTITY, _Ty fillValue = 0 );
				
				void identity( void ) { Identity( *this ); }
				
				void fill( _Ty fillValue ) { Fill( *this, fillValue ); }
				
				void scale( _Ty x, _Ty y, _Ty z ) { scale(vector3<_Ty>(x, y, z)); }
				
				void scale( const vector3<_Ty> & vec ) { }
				
				void rotate( _Ty x, _Ty y, _Ty z ) { rotate(vector3<_Ty>(x, y, z)); }
				
				void rotate( const vector3<_Ty> & vec ) { }
				
				void translate( _Ty x, _Ty y, _Ty z ) { translate(vector3<_Ty>(x, y, z)); }
				
				void translate( const vector3<_Ty> & vec ) { }
				
				void makeScale( _Ty x, _Ty y, _Ty z ) { makeScale(vector3<_Ty>(x, y, z)); }
				
				void makeScale( const vector3<_Ty> & vec ) { }
				
				void makeRotate( _Ty x, _Ty y, _Ty z ) { makeRotate(vector3<_Ty>(x, y, z)); }
				
				void makeRotate( const vector3<_Ty> & vec ) { }
				
				void makeTranslate( _Ty x, _Ty y, _Ty z ) { makeTranslate(vector3<_Ty>(x, y, z)); }
				
				void makeTranslate( const vector3<_Ty> & vec ) { }
				
			//public static
				
				static void Identity( matrix4x4 & mat )
				{
					mat.m11 = 1;	mat.m12 = 0;	mat.m13 = 0;	mat.m14 = 0;
					mat.m21 = 0;	mat.m22 = 1;	mat.m23 = 0;	mat.m24 = 0;
					mat.m31 = 0;	mat.m32 = 0;	mat.m33 = 1;	mat.m34 = 0;
					mat.m41 = 0;	mat.m42 = 0;	mat.m43 = 0;	mat.m44 = 1;
				}
				
				static matrix4x4 Identity( void )
				{
					matrix4x4 tmp;
					Identity( tmp );
					return tmp;
				}
				
				static void Fill( matrix4x4 & mat, _Ty fillValue ) { memset( mat.M, fillValue ); }
				
				static matrix4x4 Fill( _Ty fillValue )
				{
					matrix4x4 tmp;
					Fill( tmp, fillValue );
					return tmp;
				}
			};

			template<typename _Ty>
			matrix4x4<_Ty>::matrix4x4( InitializeFlag initFlag, _Ty fillValue )
			{
				switch (initFlag) {
					case INIT_IDENTITY:
						identity( );
						break;
					case INIT_ZERO:
						fill( 0 );
						break;
					case INIT_FILL:
						fill( fillValue );
						break;
					case INIT_NOTHING:
					default:
						break;
				}
			}

			typedef matrix4x4<ftype> matrix4;

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// 12 :46 Friday 13 8 2010.

