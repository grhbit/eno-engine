/*
 *  matrix4.h
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "enoMath.h"
#include "vector3d.h"
#include "vector4d.h"
#include "quaternion.h"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN
			template<typename _Ty>
			struct
#ifdef ENO_COMPILED_FROM_VISUAL_STUDIO
ENO_ALIGNED_16	//__declspec(align(16)) struct Matrix4x4
#endif
			Matrix4x4 {
			public:
				typedef _Ty element_type;
				typedef _Ty*pointer;
				
				union {
					struct {
						_Ty _11, _12, _13, _14;
						_Ty _21, _22, _23, _24;
						_Ty _31, _32, _33, _34;
						_Ty _41, _42, _43, _44;
					};

					_Ty M[16];
					_Ty m[4][4];
					
					u8 buffer[sizeof(_Ty) * 16];
				};
			} 
#ifdef ENO_COMPILED_FROM_GNUC
ENO_ALIGNED_16 //}__attribute__((aligned(16)));
#endif
;

		ENO_STRUCT_TYPE_END

		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class vector3d_template;

			template<typename _Ty>
			class vector4d_template;

			template<typename _Ty>
			class quaternion_template;

			template<typename _Ty>
			class matrix4x4_template : public struct_type::Matrix4x4<_Ty> {
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
				inline explicit matrix4x4_template( _Ty* src )
				{
					memcpy(this->M, src, sizeof(this->M));
				}

				inline matrix4x4_template(	_Ty _11, _Ty _12, _Ty _13, _Ty _14,
										    _Ty _21, _Ty _22, _Ty _23, _Ty _24,
										    _Ty _31, _Ty _32, _Ty _33, _Ty _34,
										    _Ty _41, _Ty _42, _Ty _43, _Ty _44 )
				{
					this->m11 = _11;	this->m12 = _12;
					this->m21 = _21;	this->m22 = _22;
					this->m31 = _31;	this->m32 = _32;
					this->m41 = _41;	this->m42 = _42;
					
					this->m13 = _13;	this->m14 = _14;
					this->m23 = _23;	this->m24 = _24;
					this->m33 = _33;	this->m34 = _34;
					this->m43 = _43;	this->m44 = _44;
				}
				
				inline matrix4x4_template( const matrix4x4_template & rhs )
				{
					this->m11 = rhs.m11;	this->m12 = rhs.m12;
					this->m21 = rhs.m21;	this->m22 = rhs.m22;
					this->m31 = rhs.m31;	this->m32 = rhs.m32;
					this->m41 = rhs.m41;	this->m42 = rhs.m42;
					
					this->m13 = rhs.m13;	this->m14 = rhs.m14;
					this->m23 = rhs.m23;	this->m24 = rhs.m24;
					this->m33 = rhs.m33;	this->m34 = rhs.m34;
					this->m43 = rhs.m43;	this->m44 = rhs.m44;
				}

				inline matrix4x4_template( InitializeFlag initFlag = INIT_IDENTITY, _Ty fillValue = 0 );

				_Ty&	operator () ( u8 row, u8 col )
				{
					return this->m[row][col];
				}
				
				_Ty		operator () ( u8 row, u8 col ) const
				{
					return this->m[row][col];
				}

				operator _Ty* ()
				{
					return &this->M[0]; 
				}
				
				operator const _Ty* () const
				{
					return const_cast<const _Ty*>(&this->M[0]);
				}

				inline matrix4x4_template operator + ( const matrix4x4_template & rhs ) const
				{
					return matrix4x4_template::Add(*this, rhs);
				}

				inline matrix4x4_template operator - ( const matrix4x4_template & rhs ) const
				{
					return matrix4x4_template::Subtract(*this, rhs);
				}
				
				inline matrix4x4_template operator * ( const matrix4x4_template & rhs ) const
				{
					return matrix4x4_template::Multiply(*this, rhs);
				}

				inline matrix4x4_template operator + ( const _Ty value ) const
				{
					return matrix4x4_template::Add(*this, value);
				}

				inline matrix4x4_template operator - ( const _Ty value ) const
				{
					return matrix4x4_template::Subtract(*this, value);
				}

				inline matrix4x4_template operator * ( const _Ty value ) const
				{
					return matrix4x4_template::Multiply(*this, value);
				}

				inline matrix4x4_template operator / ( const _Ty value ) const
				{
					return matrix4x4_template::Devide(*this, value);
				}

				inline matrix4x4_template & operator *= ( const matrix4x4_template & rhs )
				{
					return matrix4x4_template::multiply(rhs);
				}

				inline matrix4x4_template & operator += ( const matrix4x4_template & rhs )
				{
					return matrix4x4_template::add(rhs);
				}

				inline matrix4x4_template & operator -= ( const matrix4x4_template & rhs )
				{
					return matrix4x4_template::subtract(rhs);
				}

				inline matrix4x4_template & operator += ( _Ty value )
				{
					return matrix4x4_template::add(value);
				}

				inline matrix4x4_template & operator -= ( _Ty value )
				{
					return matrix4x4_template::subtract(value);
				}

				inline matrix4x4_template & operator *= ( _Ty value )
				{
					return matrix4x4_template::multiply( value );
				}

				inline matrix4x4_template & operator /= ( _Ty value )
				{
					return matrix4x4_template::devide( value );
				}

				inline matrix4x4_template operator + ( void ) const
				{
					return *this;
				}

				inline matrix4x4_template operator - ( void ) const
				{
					return matrix4x4_template::Multiply(*this, -1);
				}

				inline bool operator == ( const matrix4x4_template & rhs ) const
				{
					return Equals(*this, rhs);
				}

				inline bool operator != ( const matrix4x4_template & rhs ) const
				{
					return !Equals(*this, rhs);
				}

				inline matrix4x4_template& identity( void ) { Identity( *this ); return *this; }

				inline bool isIdentity( void ) { return IsIdentity( *this ); }

				inline matrix4x4_template& add( const matrix4x4_template & rhs )
				{
					matrix4x4_template::Add(*this, *this, rhs);
					return *this;
				}

				inline matrix4x4_template& add( const matrix4x4_template & lhs, const matrix4x4_template & rhs )
				{
					matrix4x4_template::Add(*this, lhs, rhs);
					return *this;
				}

				inline matrix4x4_template& add( const _Ty value )
				{
					matrix4x4_template::Add(*this, *this, value);
					return *this;
				}

				inline matrix4x4_template& add( const matrix4x4_template & lhs, const _Ty value )
				{
					matrix4x4_template::Add(*this, lhs, value);
					return *this;
				}

				inline matrix4x4_template& subtract( const matrix4x4_template & rhs )
				{
					matrix4x4_template::Subtract(*this, *this, rhs );
					return *this;
				}

				inline matrix4x4_template& subtract( const matrix4x4_template & lhs, const matrix4x4_template & rhs )
				{
					matrix4x4_template::Subtract(*this, lhs, rhs);
					return *this;
				}

				inline matrix4x4_template& subtract( const _Ty value )
				{
					matrix4x4_template::Subtract(*this, *this, value);
					return *this;
				}

				inline matrix4x4_template& subtract( const matrix4x4_template& lhs, const _Ty value )
				{
					matrix4x4_template::Subtract(*this, lhs, value);
					return *this;
				}
				
				inline matrix4x4_template& multiply( const _Ty value )
				{
					matrix4x4_template::Multiply(*this, *this, value);
					return *this;
				}

				inline matrix4x4_template& multiply( const matrix4x4_template& lhs, const _Ty value )
				{
					matrix4x4_template::Multiply(*this, lhs, value);
					return *this;
				}

				inline matrix4x4_template& devide( const _Ty value )
				{
					matrix4x4_template::Devide(*this, *this, value);
					return *this;
				}

				inline matrix4x4_template& devide( const matrix4x4_template& lhs, const _Ty value )
				{
					matrix4x4_template::Devide(*this, lhs, value);
					return *this;
				}

				inline matrix4x4_template& fill( _Ty fillValue ) { Fill( *this, fillValue ); return *this; }
				
				inline matrix4x4_template& multiply( const matrix4x4_template& mat )
				{
					matrix4x4_template::Multiply(*this, *this, mat);
					return *this;
				}
				
				inline matrix4x4_template& multiply( const matrix4x4_template& lhs, const matrix4x4_template& rhs )
				{
					matrix4x4_template::Multiply(*this, lhs, rhs);
					return *this;
				}
				
				inline matrix4x4_template& multiplyLocal( const matrix4x4_template& mat )
				{
					matrix4x4_template::Multiply(*this, mat, *this);
					return *this;
				}
				
				inline matrix4x4_template& scale( _Ty x, _Ty y, _Ty z )
				{
					return scale(vector3d_template<_Ty>(x, y, z));
				}
				
				inline matrix4x4_template& scale( const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeScale(tmp, vec3);
					matrix4x4_template::Multiply(*this, *this, tmp);
					return *this;
				}
				
				inline matrix4x4_template& rotate( _Ty x, _Ty y, _Ty z ) { return rotate(vector3d_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& rotate( const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotate(tmp, vec3);
					matrix4x4_template::Multiply(*this, *this, tmp);
					return *this;
				}

				inline matrix4x4_template& rotateX( _Ty x )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateX(tmp, x);
					matrix4x4_template::Multiply(*this, *this, tmp);
					return *this;
				}

				inline matrix4x4_template& rotateY( _Ty y )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateY(tmp, y);
					matrix4x4_template::Multiply(*this, *this, tmp);
					return *this;
				}

				inline matrix4x4_template& rotateZ( _Ty z )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateZ(tmp, z);
					matrix4x4_template::Multiply(*this, *this, tmp);
					return *this;
				}

				inline matrix4x4_template& rotateAxis( const vector3d_template<_Ty>& vec3, const _Ty value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateAxis(tmp, vec3, value);
					matrix4x4_template::Multiply(*this, *this, tmp);
					return *this;
				}
				
				inline matrix4x4_template& translate( _Ty x, _Ty y, _Ty z ) { return translate(vector3d_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& translate( const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeTranslate(tmp, vec3);
					matrix4x4_template::Multiply(*this, *this, tmp);
					return *this;
				}
				
				inline matrix4x4_template& makeScale( _Ty x, _Ty y, _Ty z ) { return makeScale(vector3d_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& makeScale( const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template::MakeScale(*this, vec3);
					return *this;
				}
				
				inline matrix4x4_template& makeRotate( ftype x, ftype y, ftype z ) { return makeRotate(vector3d_template<ftype>(x, y, z)); }
				
				inline matrix4x4_template& makeRotate( const vector3d_template<ftype> & vec3 )
				{
					matrix4x4_template::MakeRotate(*this, vec3);
					return *this;
				}
				
				inline matrix4x4_template& makeRotateX( ftype value )
				{
					matrix4x4_template::MakeRotateX(*this, value);
					return *this;
				}

				inline matrix4x4_template& makeRotateY( ftype value )
				{
					matrix4x4_template::MakeRotateY(*this, value);
					return *this;
				}
				
				inline matrix4x4_template& makeRotateZ( ftype value )
				{
					matrix4x4_template::MakeRotateZ(*this, value);
					return *this;
				}

				inline matrix4x4_template& makeRotateYawPitchRoll( ftype yaw, ftype pitch, ftype roll )
				{
					return makeRotateYawPitchRoll(vector3d_template<ftype>(pitch, yaw, roll));
				}

				inline matrix4x4_template& makeRotateYawPitchRoll( const vector3d_template<ftype> & vec3 )
				{
					matrix4x4_template::MakeRotateYawPitchRoll(*this, vec3);
					return *this;
				}

				inline matrix4x4_template& makeRotateAxis( const vector3d_template<ftype> & vec3, const _Ty value )
				{
					matrix4x4_template::MakeRotateAxis(*this, vec3, value);
					return *this;
				}
				
				inline matrix4x4_template& makeTranslate( _Ty x, _Ty y, _Ty z ) { return makeTranslate(vector3d_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& makeTranslate( const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template::MakeTranslate(*this, vec3);
					return *this;
				}
				
				inline _Ty determinant( void )
				{
					return matrix4x4_template::Determinant(*this);
				}
				
				inline matrix4x4_template& inverse( void )
				{
					matrix4x4_template::Inverse(*this, *this);
					return *this;
				}
				
				inline matrix4x4_template& inverse( const matrix4x4_template & mat )
				{
					matrix4x4_template::Inverse(*this, mat);
					return *this;
				}
				
				inline matrix4x4_template& transpose( void )
				{
					matrix4x4_template::Transpose( *this, *this );
					return *this;
				}

				inline bool equals( const matrix4x4_template& rhs, const _Ty error_range = 0.00001f )
				{
					return matrix4x4_template::Equals(  rhs, error_range );
				}

			//public static
			public:
				
				inline static void Identity( matrix4x4_template & mat )
				{
					mat.m11 = 1;	mat.m12 = 0;	mat.m13 = 0;	mat.m14 = 0;
					mat.m21 = 0;	mat.m22 = 1;	mat.m23 = 0;	mat.m24 = 0;
					mat.m31 = 0;	mat.m32 = 0;	mat.m33 = 1;	mat.m34 = 0;
					mat.m41 = 0;	mat.m42 = 0;	mat.m43 = 0;	mat.m44 = 1;
				}
				
				inline static matrix4x4_template Identity( void )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Identity( tmp );
					return tmp;
				}
				
				inline static bool IsIdentity( const matrix4x4_template & mat )
				{
					return	mat.m11 == 1 && mat.m12 == 0 && mat.m13 == 0 && mat.m14 == 0 &&
							mat.m21 == 0 && mat.m22 == 1 && mat.m23 == 0 && mat.m24 == 0 &&
							mat.m31 == 0 && mat.m32 == 0 && mat.m33 == 1 && mat.m34 == 0 &&
							mat.m41 == 0 && mat.m42 == 0 && mat.m43 == 0 && mat.m44 == 1;
				}

				inline static void Add( matrix4x4_template & mat, const matrix4x4_template & lhs, const matrix4x4_template & rhs );

				inline static matrix4x4_template Add( const matrix4x4_template & lhs, const matrix4x4_template & rhs )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Add(tmp, lhs, rhs);
					return tmp;
				}

				inline static void Add( matrix4x4_template & mat, const matrix4x4_template & lhs, _Ty value );

				inline static matrix4x4_template Add( const matrix4x4_template & mat, _Ty value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Add(tmp, mat, value);
					return tmp;
				}

				inline static void Subtract( matrix4x4_template & mat, const matrix4x4_template & lhs, const matrix4x4_template & rhs );

				inline static matrix4x4_template Subtract( const matrix4x4_template & lhs, const matrix4x4_template & rhs )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Subtract(tmp, lhs, rhs);
					return tmp;
				}

				inline static void Subtract( matrix4x4_template & mat, const matrix4x4_template & lhs, _Ty value );

				inline static matrix4x4_template Subtract( const matrix4x4_template & mat, _Ty value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Subtract(tmp, mat, value);
					return tmp;
				}
				
				inline static void Multiply( matrix4x4_template & mat, const matrix4x4_template & lhs, const _Ty value );

				inline static matrix4x4_template Multiply( const matrix4x4_template & mat, _Ty value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Multiply(tmp, mat, value);
					return tmp;
				}

				inline static void Devide( matrix4x4_template & mat, const matrix4x4_template & lhs, const _Ty value );

				inline static matrix4x4_template Devide( const matrix4x4_template & mat, _Ty value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Devide(tmp, mat, value);
					return tmp;
				}
				
				inline static void Fill( matrix4x4_template & mat, _Ty fillValue ) { for(u8 u = 0; u < 16; u++) mat.M[u] = fillValue; }
				
				inline static void Multiply( matrix4x4_template & mat, const matrix4x4_template & lhs, const matrix4x4_template & rhs );
				
				inline static matrix4x4_template Multiply( const matrix4x4_template & lhs, const matrix4x4_template & rhs )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Multiply(tmp, lhs, rhs);
					return tmp;
				}
				
				inline static matrix4x4_template Fill( _Ty fillValue )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Fill( tmp, fillValue );
					return tmp;
				}
				
				inline static void MakeScale( matrix4x4_template & mat, const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template::Identity(mat);
					mat.m11 = vec3.x;
					mat.m22 = vec3.y;
					mat.m33 = vec3.z;
				}
				
				inline static matrix4x4_template MakeScale( const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeScale(tmp, vec3);
					return tmp;
				}

				//Z * Y * X
				inline static void MakeRotate( matrix4x4_template & mat, const vector3d_template<ftype> & vec3 )
				{
					const ftype xCos = cos(vec3.x);
					const ftype xSin = sin(vec3.x);
					const ftype yCos = cos(vec3.y);
					const ftype ySin = sin(vec3.y);
					const ftype zCos = cos(vec3.z);
					const ftype zSin = sin(vec3.z);
					
					mat.m11 = yCos * zCos;
					mat.m12 = (xCos * zSin) + (xSin * ySin * zCos);
					mat.m13 = (xSin * zSin) - (xCos * ySin * zCos);
					mat.m14 = 0;
					
					mat.m21 = -(yCos * zSin);
					mat.m22 = (xCos * zCos) - (xSin * ySin * zSin);
					mat.m23 = (xSin * zCos) + (xCos * ySin * zSin);
					mat.m24 = 0;
					
					mat.m31 = ySin;
					mat.m32 = -(xSin * yCos);
					mat.m33 = xCos * yCos;
					mat.m34 = 0;
					
					mat.m41 = 0;
					mat.m42 = 0;
					mat.m43 = 0;
					mat.m44 = 1;
				}

				inline static matrix4x4_template MakeRotate( const vector3d_template<ftype> & vec3 )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotate(tmp, vec3);
					return tmp;
				}
				
				inline static void MakeRotateX( matrix4x4_template & mat, ftype value )
				{
					matrix4x4_template::Identity(mat);
					mat.m22 = cos(value);
					mat.m33 = mat.m22;
					
					mat.m23 = sin(value);
					mat.m32 = -mat.m23;
				}

				inline static matrix4x4_template MakeRotateX( ftype value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateX(tmp, value);
					return tmp;
				}
				
				inline static void MakeRotateY( matrix4x4_template & mat, ftype value )
				{
					matrix4x4_template::Identity(mat);
					mat.m11 = cos(value);
					mat.m33 = mat.m11;
					
					mat.m31 = sin(value);
					mat.m13 = -mat.m31;
				}
				
				inline static matrix4x4_template MakeRotateY( ftype value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateY(tmp, value);
					return tmp;
				}
								
				inline static void MakeRotateZ( matrix4x4_template & mat, ftype value )
				{
					matrix4x4_template::Identity(mat);
					mat.m11 = cos(value);
					mat.m22 = mat.m11;
					
					mat.m12 = sin(value);
					mat.m21 = -mat.m12;
				}
				
				inline static matrix4x4_template MakeRotateZ( ftype value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateZ(tmp, value);
					return tmp;
				}

				inline static void MakeRotateYawPitchRoll( matrix4x4_template & mat, const vector3d_template<ftype> & vec3 )
				{
					const ftype yCos = cos(vec3.y);
					const ftype ySin = sin(vec3.y);
					const ftype xCos = cos(vec3.x);
					const ftype xSin = sin(vec3.x);
					const ftype zCos = cos(vec3.z);
					const ftype zSin = sin(vec3.z);

					mat.m11 = (yCos * zCos) + (ySin * xSin * zSin);
					mat.m12 = (xCos * zSin);
					mat.m13 = -(ySin * zCos) + (xSin * yCos * zSin);
					mat.m14 = 0;

					mat.m21 = -(yCos * zSin) + (ySin * xSin * zCos);
					mat.m22 = xCos * zCos;
					mat.m23 = (ySin * zSin) + (xSin * yCos * zCos);
					mat.m24 = 0;

					mat.m31 = (xCos * ySin);
					mat.m32 = -xSin;
					mat.m33 = xCos * yCos;
					mat.m34 = 0;

					mat.m41 = 0;
					mat.m42 = 0;
					mat.m43 = 0;
					mat.m44 = 1;
				}

				inline static matrix4x4_template MakeRotateYawPitchRoll( const vector3d_template<ftype> & vec3 )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::makeRotateYawPitchRoll(tmp, vec3);
					return tmp;
				}

				inline static void MakeRotateAxis( matrix4x4_template & mat, const vector3d_template<ftype> & vec3, const _Ty value )
				{
					const ftype c = cos(value);
					const ftype s = sin(value);
					const ftype t = 1.0 - c;

					mat.m11 = c + (vec3.x * vec3.x * t);
					mat.m22 = c + (vec3.y * vec3.y * t);
					mat.m33 = c + (vec3.z * vec3.z * t);

					ftype tmp1 = (vec3.x * vec3.y * t);
					ftype tmp2 = (vec3.z * s);
					mat.m12 = tmp1 + tmp2;
					mat.m21 = tmp1 - tmp2;

					tmp1 = (vec3.x * vec3.z * t);
					tmp2 = (vec3.y * s);
					mat.m13 = tmp1 + tmp2;
					mat.m31 = tmp1 - tmp2;

					tmp1 = (vec3.y * vec3.z * t);
					tmp2 = (vec3.x * s);
					mat.m23 = tmp1 + tmp2;
					mat.m32 = tmp1 - tmp2;
				}

				inline static matrix4x4_template MakeRotateAxis( const vector3d_template<ftype> & vec3, const _Ty value )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateAxis( tmp, vec3, value );
					return tmp;
				}

				inline static void MakeRotateQuaternion( matrix4x4_template & mat, const quaternion_template<_Ty> & quat )
				{
					_Ty xx = quat.x * quat.x;
					_Ty yy = quat.y * quat.y;
					_Ty zz = quat.z * quat.z;
					_Ty xy = quat.x * quat.y;
					_Ty xz = quat.x * quat.z;
					_Ty xw = quat.x * quat.w;
					_Ty yz = quat.y * quat.z;
					_Ty yw = quat.y * quat.w;
					_Ty zw = quat.z * quat.w;

					mat.m11 = 1 - (2 * (yy + zz));
					mat.m12 = (2 * xy) + (2 * zw);
					mat.m13 = (2 * xz) - (2 * yw);
					mat.m14 = 0;

					mat.m21 = (2 * xy) - (2 * zw);
					mat.m22 = 1 - (2 * (xx + zz));
					mat.m23 = (2 * yz) + (2 * xw);
					mat.m24 = 0;

					mat.m31 = (2 * xz) + (2 * yw);
					mat.m32 = (2 * yz) - (2 * xw);
					mat.m33 = 1 - (2 * (xx + yy));
					mat.m34 = 0;

					mat.m41 = 0; mat.m42 = 0; mat.m43 = 0; mat.m44 = 1;
				}

				inline static matrix4x4_template MakeRotateQuaternion( const quaternion_template<_Ty> & quat )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeRotateQuaternion(tmp, quat);
					return tmp;
				}
				
				inline static void MakeTranslate( matrix4x4_template & mat, const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template::Identity(mat);
					mat.m41 = vec3.x;
					mat.m42 = vec3.y;
					mat.m43 = vec3.z;
				}
				
				inline static matrix4x4_template MakeTranslate( const vector3d_template<_Ty> & vec3 )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::MakeTranslate(tmp, vec3);
					return tmp;
				}

				inline static vector3d_template<_Ty> TakeScale( const matrix4x4_template & mat )
				{
					if ((mat.m12 == 0) && (mat.m13 == 0) && 
						(mat.m21 == 0) && (mat.m23 == 0) &&
						(mat.m31 == 0) && (mat.m32 == 0)) {
						return vector3d_template<_Ty>(mat.m11, mat.m22, mat.m33);
					}
					
					return vector3d_template<_Ty>( 
						sqrt((mat.m11 * mat.m11) + (mat.m12 * mat.m12) + (mat.m13 * mat.m13)),
						sqrt((mat.m21 * mat.m21) + (mat.m22 * mat.m22) + (mat.m23 * mat.m23)),
						sqrt((mat.m31 * mat.m31) + (mat.m32 * mat.m32) + (mat.m33 * mat.m33)) );
				}

				inline static void TakeScale( vector3d_template<_Ty> & vec3, const matrix4x4_template & mat )
				{
					vec3 = TakeScale(mat);
				}

				inline static quaternion_template<_Ty> TakeRotate( const matrix4x4_template & mat )
				{
				}

				inline static void TakeRotate( quaternion_template<_Ty> & quat, const matrix4x4_template & mat )
				{
					quat = TakeRotate(mat);
				}

				inline static vector3d_template<_Ty> TakeTranslate( const matrix4x4_template & mat )
				{
					return vector3d_template<_Ty>( mat.m41, mat.m42, mat.m43 );
				}

				inline static void TakeTranslate( vector3d_template<_Ty> & vec3, const matrix4x4_template & mat )
				{
					vec3 = TakeTranslate(mat);
				}
				
				inline static _Ty Determinant( const matrix4x4_template & mat );
			
				inline static void Inverse( matrix4x4_template & out, const matrix4x4_template & mat );
				
				inline static matrix4x4_template Inverse( const matrix4x4_template & mat )
				{
					matrix4x4_template tmp(INIT_NOTHING);
					matrix4x4_template::Inverse(tmp, mat);
					return mat;
				}
				
				inline static void Transpose( matrix4x4_template & out, const matrix4x4_template & mat );

				inline static bool Equals( matrix4x4_template & lhs, matrix4x4_template & rhs, _Ty error_range = 0 )
				{
					for ( u8 i = 0; i < 16; i++ )
						if (equals(lhs.M[i], rhs.M[i], error_range))
							return false;

					return true;
				}
			};

			template<typename _Ty>
			matrix4x4_template<_Ty>::matrix4x4_template( InitializeFlag initFlag, _Ty fillValue )
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

			template<typename _Ty>
			_Ty matrix4x4_template<_Ty>::Determinant( const matrix4x4_template & mat )
			{
				return (
						(mat.m11*mat.m22*mat.m33)+
						(mat.m12*mat.m23*mat.m31)+
						(mat.m13*mat.m21*mat.m32)
						)
						-
						(
						(mat.m13*mat.m22*mat.m31)+
						(mat.m11*mat.m23*mat.m32)+
						(mat.m12*mat.m21*mat.m33)
						);
			}

			template<typename _Ty>
			void matrix4x4_template<_Ty>::Inverse( matrix4x4_template & out, const matrix4x4_template & mat )
			{
				matrix4x4_template tmp(INIT_NOTHING);
				
				_Ty Det = matrix4x4_template::Determinant(mat);

				_Ty Inv = static_cast<_Ty>(0.0f);
				if( Det < static_cast<_Ty>(0.0f))
					return;
				else if(Det == static_cast<_Ty>(0.0f))
					Inv = 1.0f;
				else Inv = static_cast<_Ty>(1.0f)/Det;

				tmp.m11= Inv * ( mat.m22*mat.m33 - mat.m23*mat.m32 );
				tmp.m12=-Inv * ( mat.m12*mat.m33 - mat.m13*mat.m32 );
				tmp.m13= Inv * ( mat.m12*mat.m23 - mat.m13*mat.m22 );
				tmp.m14= 0.0;
				
				tmp.m21=-Inv * ( mat.m21*mat.m33 - mat.m23*mat.m31 );
				tmp.m22= Inv * ( mat.m11*mat.m33 - mat.m13*mat.m31 );
				tmp.m23=-Inv * ( mat.m11*mat.m23 - mat.m13*mat.m21 );
				tmp.m24= 0.0;
				
				tmp.m31= Inv * ( mat.m21*mat.m32 - mat.m22*mat.m31 );
				tmp.m32=-Inv * ( mat.m11*mat.m32 - mat.m12*mat.m31 );
				tmp.m33= Inv * ( mat.m11*mat.m22 - mat.m12*mat.m21 );
				tmp.m34= 0.0;
				
				tmp.m41=-(mat.m41*tmp.m11+mat.m42*tmp.m21+mat.m43*tmp.m31);
				tmp.m42=-(mat.m41*tmp.m12+mat.m42*tmp.m22+mat.m43*tmp.m32);
				tmp.m43=-(mat.m41*tmp.m13+mat.m42*tmp.m23+mat.m43*tmp.m33);
				tmp.m44= 1.0;
				
				out = tmp;
			}

			template<typename _Ty>
			void matrix4x4_template<_Ty>::Transpose( matrix4x4_template & out, const matrix4x4_template & mat )
			{
				matrix4x4_template tmp( INIT_NOTHING );
				for (u8 i = 0; i < 16; i++)
					for (u8 j = 0; j < 16; j++)
						tmp.m[i][j] = mat[j][i];
				
				out = tmp;
			}

			typedef matrix4x4_template<ftype> matrix4x4;
			typedef matrix4x4_template<f32> matrix4x4_f32;

		ENO_CLASS_TYPE_END

		ENO_FUNCTION_BEGIN

			template<typename _Ty>
			inline void multMatrix( class_type::matrix4x4_template<_Ty>& out, 
							const class_type::matrix4x4_template<_Ty>& a, 
							const class_type::matrix4x4_template<_Ty>& b )
			{
				out = class_type::matrix4x4_template<_Ty>(
					  b.m11*a.m11+b.m12*a.m21+b.m13*a.m31+b.m14*a.m41,
					  b.m11*a.m12+b.m12*a.m22+b.m13*a.m32+b.m14*a.m42,
					  b.m11*a.m13+b.m12*a.m23+b.m13*a.m33+b.m14*a.m43,
					  b.m11*a.m14+b.m12*a.m24+b.m13*a.m34+b.m14*a.m44,
					  b.m21*a.m11+b.m22*a.m21+b.m23*a.m31+b.m24*a.m41,
					  b.m21*a.m12+b.m22*a.m22+b.m23*a.m32+b.m24*a.m42,
					  b.m21*a.m13+b.m22*a.m23+b.m23*a.m33+b.m24*a.m43,
					  b.m21*a.m14+b.m22*a.m24+b.m23*a.m34+b.m24*a.m44,
					  b.m31*a.m11+b.m32*a.m21+b.m33*a.m31+b.m34*a.m41,
					  b.m31*a.m12+b.m32*a.m22+b.m33*a.m32+b.m34*a.m42,
					  b.m31*a.m13+b.m32*a.m23+b.m33*a.m33+b.m34*a.m43,
					  b.m31*a.m14+b.m32*a.m24+b.m33*a.m34+b.m34*a.m44,
					  b.m41*a.m11+b.m42*a.m21+b.m43*a.m31+b.m44*a.m41,
					  b.m41*a.m12+b.m42*a.m22+b.m43*a.m32+b.m44*a.m42,
					  b.m41*a.m13+b.m42*a.m23+b.m43*a.m33+b.m44*a.m43,
					  b.m41*a.m14+b.m42*a.m24+b.m43*a.m34+b.m44*a.m44 );
			}

			template<typename _Ty>
			inline void addMatrix( class_type::matrix4x4_template<_Ty>& out,
								  const class_type::matrix4x4_template<_Ty>& a,
								  const class_type::matrix4x4_template<_Ty>& b )
			{
				out = class_type::matrix4x4_template<_Ty>(
					a.m11+b.m11, a.m12+b.m12, a.m13+b.m13, a.m14+b.m14,
					a.m21+b.m21, a.m22+b.m22, a.m23+b.m23, a.m24+b.m24,
					a.m31+b.m31, a.m32+b.m32, a.m33+b.m33, a.m34+b.m34,
					a.m41+b.m41, a.m42+b.m42, a.m43+b.m43, a.m44+b.m44
				);
			}

			template<typename _Ty>
			inline void subMatrix( class_type::matrix4x4_template<_Ty>& out,
								const class_type::matrix4x4_template<_Ty>& a,
								const class_type::matrix4x4_template<_Ty>& b )
			{
				out = class_type::matrix4x4_template<_Ty>(	
					a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13, a.m14 - b.m14,
					a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23, a.m24 - b.m24,
					a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33, a.m34 - b.m34,
					a.m41 - b.m41, a.m42 - b.m42, a.m43 - b.m43, a.m44 - b.m44 );
			}

			template<typename _Ty>
			inline void addValueMatrix( class_type::matrix4x4_template<_Ty>& out,
										const class_type::matrix4x4_template<_Ty>& a,
										const _Ty value )
			{
				out = matrix4x4_template<_Ty>(	a.m11 + value, a.m12 + value, a.m13 + value, a.m14 + value,
												a.m21 + value, a.m22 + value, a.m23 + value, a.m24 + value,
												a.m31 + value, a.m32 + value, a.m33 + value, a.m34 + value,
												a.m41 + value, a.m42 + value, a.m43 + value, a.m44 + value );
			}

			template<typename _Ty>
			inline void subtractValueMatrix( class_type::matrix4x4_template<_Ty>& out,
				const class_type::matrix4x4_template<_Ty>& a,
				const _Ty value )
			{
				out = matrix4x4_template<_Ty>(	a.m11 - value, a.m12 - value, a.m13 - value, a.m14 - value,
												a.m21 - value, a.m22 - value, a.m23 - value, a.m24 - value,
												a.m31 - value, a.m32 - value, a.m33 - value, a.m34 - value,
												a.m41 - value, a.m42 - value, a.m43 - value, a.m44 - value );
			}

			template<typename _Ty>
			inline void multiplyValueMatrix( class_type::matrix4x4_template<_Ty>& out,
											const class_type::matrix4x4_template<_Ty>& a,
											const _Ty value )
			{
				out = matrix4x4_template<_Ty>(	a.m11 * value, a.m12 * value, a.m13 * value, a.m14 * value,
												a.m21 * value, a.m22 * value, a.m23 * value, a.m24 * value,
												a.m31 * value, a.m32 * value, a.m33 * value, a.m34 * value,
												a.m41 * value, a.m42 * value, a.m43 * value, a.m44 * value );
			}

			template<typename _Ty>
			inline void devideValueMatrix( class_type::matrix4x4_template<_Ty>& out,
				const class_type::matrix4x4_template<_Ty>& a,
				const _Ty value )
			{
				_Ty inv = 1.0/value;
				out = matrix4x4_template<_Ty>(	a.m11 * inv, a.m12 * inv, a.m13 * inv, a.m14 * inv,
												a.m21 * inv, a.m22 * inv, a.m23 * inv, a.m24 * inv,
												a.m31 * inv, a.m32 * inv, a.m33 * inv, a.m34 * inv,
												a.m41 * inv, a.m42 * inv, a.m43 * inv, a.m44 * inv );
			}

			template<typename _Ty>
			struct matrixUtil {
				static void (* multiply)( class_type::matrix4x4_template<_Ty>&, 
										 const class_type::matrix4x4_template<_Ty>&, 
										 const class_type::matrix4x4_template<_Ty>& );
				
				static void (* add)( class_type::matrix4x4_template<_Ty>&,
									const class_type::matrix4x4_template<_Ty>&,
									const class_type::matrix4x4_template<_Ty>& );

				static void (* subtract)( class_type::matrix4x4_template<_Ty>&,
									const class_type::matrix4x4_template<_Ty>&,
									const class_type::matrix4x4_template<_Ty>& );

				static void (* addValue)( class_type::matrix4x4_template<_Ty>&,
										const class_type::matrix4x4_template<_Ty>&,
										const _Ty value );

				static void (* subtractValue)( class_type::matrix4x4_template<_Ty>&,
										const class_type::matrix4x4_template<_Ty>&,
										const _Ty value );

				static void (* multiplyValue)( class_type::matrix4x4_template<_Ty>&,
										const class_type::matrix4x4_template<_Ty>&,
										const _Ty value );

				static void (* devideValue)( class_type::matrix4x4_template<_Ty>&,
										const class_type::matrix4x4_template<_Ty>&,
										const _Ty value );
			};

			template<typename _Ty>
			void (* matrixUtil<_Ty>::multiply)( class_type::matrix4x4_template<_Ty>& out, 
											   const class_type::matrix4x4_template<_Ty>& first, 
											   const class_type::matrix4x4_template<_Ty>& second ) = multMatrix;

			template<typename _Ty>
			void (* matrixUtil<_Ty>::add)( class_type::matrix4x4_template<_Ty>& out,
										  const class_type::matrix4x4_template<_Ty>& first,
										  const class_type::matrix4x4_template<_Ty>& second ) = addMatrix;

			template<typename _Ty>
			void (* matrixUtil<_Ty>::subtract)( class_type::matrix4x4_template<_Ty>&,
											const class_type::matrix4x4_template<_Ty>&,
											const class_type::matrix4x4_template<_Ty>& ) = subMatrix;

			template<typename _Ty>
			void (* matrixUtil<_Ty>::addValue)( class_type::matrix4x4_template<_Ty>&,
												const class_type::matrix4x4_template<_Ty>&,
												const _Ty value ) = addValueMatrix;

			template<typename _Ty>
			void (* matrixUtil<_Ty>::subtractValue)( class_type::matrix4x4_template<_Ty>&,
													const class_type::matrix4x4_template<_Ty>&,
													const _Ty value ) = subtractValueMatrix;

			template<typename _Ty>
			void (* matrixUtil<_Ty>::multiplyValue)( class_type::matrix4x4_template<_Ty>&,
													const class_type::matrix4x4_template<_Ty>&,
													const _Ty value ) = multiplyValueMatrix;

			template<typename _Ty>
			void (* matrixUtil<_Ty>::devideValue)( class_type::matrix4x4_template<_Ty>&,
												const class_type::matrix4x4_template<_Ty>&,
												const _Ty value ) = devideValueMatrix;

			template<typename _Ty>
			inline void multiplyMatrixSSE( class_type::matrix4x4_template<_Ty>& out,
							  const class_type::matrix4x4_template<f32>& a,
							  const class_type::matrix4x4_template<f32>& b )
			{
				multMatrix(out, a, b);
			}

			template<>
			inline void multiplyMatrixSSE( class_type::matrix4x4_template<f32>& out, 
								   const class_type::matrix4x4_template<f32>& a, 
								   const class_type::matrix4x4_template<f32>& b )
			{
				f32 * dst = out.M;
				f32 * lhs = const_cast<f32*>(a.M);
				f32 * rhs = const_cast<f32*>(b.M);
#if defined (ENO_COMPILED_FROM_GNUC)
				asm __volatile__(
								 "movaps (%%ecx)  ,	%%xmm0\n\t"	// xmm0 = src1[00, 01, 02, 03]
								 "movaps 10(%%ecx),	%%xmm1\n\t"	// xmm1 = src1[04, 05, 06, 07]
								 "movaps 20(%%ecx),	%%xmm2\n\t"	// xmm2 = src1[08, 09, 10, 11]
								 "movaps 30(%%ecx),	%%xmm3\n\t"	// xmm3 = src1[12, 13, 14, 15]

								 "movss	(%%edx)	  ,	%%xmm7\n\t"		// xmm7 = src2[00, xx, xx, xx]
								 "movss	4(%%edx)  ,	%%xmm4\n\t"		// xmm4 = src2[01, xx, xx, xx]
								 "movss	8(%%edx)  ,	%%xmm5\n\t"		// xmm5 = src2[02, xx, xx, xx]
								 "movss	0xc(%%edx),	%%xmm6\n\t"		// xmm6 = src2[03, xx, xx, xx]
				 
								 "shufps $0x0, %%xmm7,  %%xmm7\n\t"		// xmm7 = src2[00, 00, 00, 00]
								 "shufps $0x0, %%xmm4,	%%xmm4\n\t"		// xmm4 = src2[01, 01, 01, 01]
								 "shufps $0x0, %%xmm5,	%%xmm5\n\t"		// xmm5 = src2[02, 02, 02, 02]
								 "shufps $0x0, %%xmm6,	%%xmm6\n\t"		// xmm6 = src2[03, 03, 03, 03]
								 
								 "mulps	%%xmm0,	%%xmm7\n\t"			// xmm7 *= xmm0
								 "mulps	%%xmm1,	%%xmm4\n\t"			// xmm4 *= xmm1
								 "mulps	%%xmm2,	%%xmm5\n\t"			// xmm5 *= xmm2
								 "mulps	%%xmm3,	%%xmm6\n\t"			// xmm6 *= xmm3
								 
								 "addps	%%xmm4,	%%xmm7\n\t"			// xmm7 += xmm4
								 "addps	%%xmm5,	%%xmm7\n\t"			// xmm7 += xmm5
								 "addps	%%xmm6,	%%xmm7\n\t"			// xmm7 += xmm6
				 
								 "movaps %%xmm7, (%%eax)\n\t"		// eax = xmm7
								 
								 "movss	0x10(%%edx),	%%xmm7\n\t"	// xmm7 = src2[04, xx, xx, xx]
								 "movss	0x14(%%edx),	%%xmm4\n\t"	// xmm4 = src2[05, xx, xx, xx]
								 "movss	0x18(%%edx),	%%xmm5\n\t"	// xmm5 = src2[06, xx, xx, xx]
								 "movss	0x1c(%%edx),	%%xmm6\n\t"	// xmm6 = src2[07, xx, xx, xx]
								
								 "shufps $0x0, 	%%xmm7,	%%xmm7\n\t"		// xmm7 = src2[04, 04, 04, 04]
								 "shufps $0x0, 	%%xmm4,	%%xmm4\n\t"		// xmm4 = src2[05, 05, 05, 05]
								 "shufps $0x0, 	%%xmm5,	%%xmm5\n\t"		// xmm5 = src2[06, 06, 06, 06]
								 "shufps $0x0, 	%%xmm6,	%%xmm6\n\t"		// xmm6 = src2[07, 07, 07, 07]
								 
								 "mulps	%%xmm0,	%%xmm7\n\t"			// xmm7 *= xmm0
								 "mulps	%%xmm1,	%%xmm4\n\t"			// xmm4 *= xmm1
								 "mulps	%%xmm2,	%%xmm5\n\t"			// xmm5 *= xmm2
								 "mulps	%%xmm3,	%%xmm6\n\t"			// xmm6 *= xmm3
								 
								 "addps	%%xmm4,	%%xmm7\n\t"			// xmm7 += xmm4
								 "addps	%%xmm5,	%%xmm7\n\t"			// xmm7 += xmm5
								 "addps	%%xmm6,	%%xmm7\n\t"			// xmm7 += xmm6
								 
								 "movaps %%xmm7, 0x10(%%eax)\n\t"	// eax = xmm7
				 
								 "movss	0x20(%%edx),	%%xmm7\n\t"	// xmm7 = src2[08, xx, xx, xx]
								 "movss	0x24(%%edx),	%%xmm4\n\t"	// xmm4 = src2[09, xx, xx, xx]
								 "movss	0x28(%%edx),	%%xmm5\n\t"	// xmm5 = src2[10, xx, xx, xx]
								 "movss	0x2c(%%edx),	%%xmm6\n\t"	// xmm6 = src2[11, xx, xx, xx]
								 
								 "shufps $0x0,	%%xmm7,	%%xmm7\n\t"		// xmm7 = src2[08, 08, 08, 08]
								 "shufps $0x0, 	%%xmm4,	%%xmm4\n\t"		// xmm4 = src2[09, 09, 09, 09]
								 "shufps $0x0, 	%%xmm5,	%%xmm5\n\t"		// xmm5 = src2[10, 10, 10, 10]
								 "shufps $0x0, 	%%xmm6,	%%xmm6\n\t"		// xmm6 = src2[11, 11, 11, 11]
								 
								 "mulps	%%xmm0,	%%xmm7\n\t"			// xmm7 *= xmm0
								 "mulps	%%xmm1,	%%xmm4\n\t"			// xmm4 *= xmm1
								 "mulps	%%xmm2,	%%xmm5\n\t"			// xmm5 *= xmm2
								 "mulps	%%xmm3,	%%xmm6\n\t"			// xmm6 *= xmm3
								 
								 "addps	%%xmm4,	%%xmm7\n\t"			// xmm7 += xmm4
								 "addps	%%xmm5,	%%xmm7\n\t"			// xmm7 += xmm5
								 "addps	%%xmm6,	%%xmm7\n\t"			// xmm7 += xmm6
								 
								 "movaps %%xmm7, 0x20(%%eax)\n\t"	// eax = xmm7									 
				 
								 "movss	0x30(%%edx),	%%xmm7\n\t"	// xmm7 = src2[12, xx, xx, xx]
								 "movss	0x34(%%edx),	%%xmm4\n\t"	// xmm4 = src2[13, xx, xx, xx]
								 "movss	0x38(%%edx),	%%xmm5\n\t"	// xmm5 = src2[14, xx, xx, xx]
								 "movss	0x3c(%%edx),	%%xmm6\n\t"	// xmm6 = src2[15, xx, xx, xx]
								 
								 "shufps $0x0, 	%%xmm7,	%%xmm7\n\t"		// xmm7 = src2[12, 12, 12, 12]
								 "shufps $0x0, 	%%xmm4,	%%xmm4\n\t"		// xmm4 = src2[13, 13, 13, 13]
								 "shufps $0x0, 	%%xmm5,	%%xmm5\n\t"		// xmm5 = src2[14, 14, 14, 14]
								 "shufps $0x0, 	%%xmm6,	%%xmm6\n\t"		// xmm6 = src2[15, 15, 15, 15]
								 
								 "mulps	%%xmm0,	%%xmm7\n\t"			// xmm7 *= xmm0
								 "mulps	%%xmm1,	%%xmm4\n\t"			// xmm4 *= xmm1
								 "mulps	%%xmm2,	%%xmm5\n\t"			// xmm5 *= xmm2
								 "mulps	%%xmm3,	%%xmm6\n\t"			// xmm6 *= xmm3
								 
								 "addps	%%xmm4,	%%xmm7\n\t"			// xmm7 += xmm4
								 "addps	%%xmm5,	%%xmm7\n\t"			// xmm7 += xmm5
								 "addps	%%xmm6,	%%xmm7\n\t"			// xmm7 += xmm6
								 
								 "movaps %%xmm7, 0x30(%%eax)"		// eax = xmm7
								 :
								 : "a"(dst), "c"(lhs), "d"(rhs)
								 : "memory"
								 );
#elif defined (ENO_COMPILED_FROM_VISUAL_STUDIO)
				__asm
				{
					mov		eax,	dst		// dst
					mov		ecx,	lhs		// src1
					mov		edx,	rhs		// src2

					movaps	xmm0,	xmmword ptr [ecx]		// xmm0 = src1[00, 01, 02, 03]
					movaps	xmm1,	xmmword ptr [ecx + 0x10]	// xmm1 = src1[04, 05, 06, 07]
					movaps	xmm2,	xmmword ptr [ecx + 0x20]	// xmm2 = src1[08, 09, 10, 11]
					movaps	xmm3,	xmmword ptr [ecx + 0x30]	// xmm3 = src1[12, 13, 14, 15]

					movss	xmm7,	dword ptr [edx]		// xmm7 = src2[00, xx, xx, xx]
					movss	xmm4,	dword ptr [edx + 0x4]	// xmm4 = src2[01, xx, xx, xx]
					movss	xmm5,	dword ptr [edx + 0x8]	// xmm5 = src2[02, xx, xx, xx]
					movss	xmm6,	dword ptr [edx + 0xc]		// xmm6 = src2[03, xx, xx, xx]

					shufps	xmm7,	xmm7, 0x0		// xmm7 = src2[00, 00, 00, 00]
					shufps	xmm4,	xmm4, 0x0		// xmm4 = src2[01, 01, 01, 01]
					shufps	xmm5,	xmm5, 0x0		// xmm5 = src2[02, 02, 02, 02]
					shufps	xmm6,	xmm6, 0x0		// xmm6 = src2[03, 03, 03, 03]

					mulps	xmm7,	xmm0			// xmm7 *= xmm0
					mulps	xmm4,	xmm1			// xmm4 *= xmm1
					mulps	xmm5,	xmm2			// xmm5 *= xmm2
					mulps	xmm6,	xmm3			// xmm6 *= xmm3

					addps	xmm7,	xmm4			// xmm7 += xmm4
					addps	xmm7,	xmm5			// xmm7 += xmm5
					addps	xmm7,	xmm6			// xmm7 += xmm6

					movaps	xmmword ptr [eax], xmm7		// eax = xmm7

					movss	xmm7,	dword ptr [edx + 0x10]	// xmm7 = src2[04, xx, xx, xx]
					movss	xmm4,	dword ptr [edx + 0x14]	// xmm4 = src2[05, xx, xx, xx]
					movss	xmm5,	dword ptr [edx + 0x18]	// xmm5 = src2[06, xx, xx, xx]
					movss	xmm6,	dword ptr [edx + 0x1c]	// xmm6 = src2[07, xx, xx, xx]

					shufps	xmm7,	xmm7, 0x0		// xmm7 = src2[04, 04, 04, 04]
					shufps	xmm4,	xmm4, 0x0		// xmm4 = src2[05, 05, 05, 05]
					shufps	xmm5,	xmm5, 0x0		// xmm5 = src2[06, 06, 06, 06]
					shufps	xmm6,	xmm6, 0x0		// xmm6 = src2[07, 07, 07, 07]

					mulps	xmm7,	xmm0			// xmm7 *= xmm0
					mulps	xmm4,	xmm1			// xmm4 *= xmm1
					mulps	xmm5,	xmm2			// xmm5 *= xmm2
					mulps	xmm6,	xmm3			// xmm6 *= xmm3

					addps	xmm7,	xmm4			// xmm7 += xmm4
					addps	xmm7,	xmm5			// xmm7 += xmm5
					addps	xmm7,	xmm6			// xmm7 += xmm6

					movaps	xmmword ptr [eax + 0x10], xmm7	// eax = xmm7

					movss	xmm7,	dword ptr [edx + 0x20]	// xmm7 = src2[08, xx, xx, xx]
					movss	xmm4,	dword ptr [edx + 0x24]	// xmm4 = src2[09, xx, xx, xx]
					movss	xmm5,	dword ptr [edx + 0x28]	// xmm5 = src2[10, xx, xx, xx]
					movss	xmm6,	dword ptr [edx + 0x2c]	// xmm6 = src2[11, xx, xx, xx]

					shufps	xmm7,	xmm7, 0x0		// xmm7 = src2[08, 08, 08, 08]
					shufps	xmm4,	xmm4, 0x0		// xmm4 = src2[09, 09, 09, 09]
					shufps	xmm5,	xmm5, 0x0		// xmm5 = src2[10, 10, 10, 10]
					shufps	xmm6,	xmm6, 0x0		// xmm6 = src2[11, 11, 11, 11]

					mulps	xmm7,	xmm0			// xmm7 *= xmm0
					mulps	xmm4,	xmm1			// xmm4 *= xmm1
					mulps	xmm5,	xmm2			// xmm5 *= xmm2
					mulps	xmm6,	xmm3			// xmm6 *= xmm3

					addps	xmm7,	xmm4			// xmm7 += xmm4
					addps	xmm7,	xmm5			// xmm7 += xmm5
					addps	xmm7,	xmm6			// xmm7 += xmm6

					movaps	xmmword ptr [eax + 0x20], xmm7	// eax = xmm7

					movss	xmm7,	dword ptr [edx + 0x30]	// xmm7 = src2[12, xx, xx, xx]
					movss	xmm4,	dword ptr [edx + 0x34]	// xmm4 = src2[13, xx, xx, xx]
					movss	xmm5,	dword ptr [edx + 0x38]	// xmm5 = src2[14, xx, xx, xx]
					movss	xmm6,	dword ptr [edx + 0x3c]	// xmm6 = src2[15, xx, xx, xx]

					shufps	xmm7,	xmm7, 0x0		// xmm7 = src2[12, 12, 12, 12]
					shufps	xmm4,	xmm4, 0x0		// xmm4 = src2[13, 13, 13, 13]
					shufps	xmm5,	xmm5, 0x0		// xmm5 = src2[14, 14, 14, 14]
					shufps	xmm6,	xmm6, 0x0		// xmm6 = src2[15, 15, 15, 15]

					mulps	xmm7,	xmm0			// xmm7 *= xmm0
					mulps	xmm4,	xmm1			// xmm4 *= xmm1
					mulps	xmm5,	xmm2			// xmm5 *= xmm2
					mulps	xmm6,	xmm3			// xmm6 *= xmm3

					addps	xmm7,	xmm4			// xmm7 += xmm4
					addps	xmm7,	xmm5			// xmm7 += xmm5
					addps	xmm7,	xmm6			// xmm7 += xmm6

					movaps	xmmword ptr [eax + 0x30], xmm7	// eax = xmm7
				}
#endif
			}

			template<typename _Ty>
			inline void multMatrixSSE( class_type::matrix4x4_template<_Ty>& out, 
							const class_type::matrix4x4_template<_Ty>& a, 
							const class_type::matrix4x4_template<_Ty>& b )
			{
				multiplyMatrixSSE(out, a, b);
			}

			template<typename _Ty>
			inline void addMatrixSSE( class_type::matrix4x4_template<_Ty>& out,
									 const class_type::matrix4x4_template<_Ty>& a,
									 const class_type::matrix4x4_template<_Ty>& b )
			{
				addMatrix(out, a, b);
			}

			template<>
			inline void addMatrixSSE( class_type::matrix4x4_template<f32>& out,
									 const class_type::matrix4x4_template<f32>& a,
									 const class_type::matrix4x4_template<f32>& b )
			{
				f32 * dst = out.M;
				f32 * lhs = const_cast<f32*>(a.M);
				f32 * rhs = const_cast<f32*>(b.M);
				
#if defined (ENO_COMPILED_FROM_GNUC)
				
				asm __volatile__ (
								  "movaps (%%ecx)	,	%%xmm0\n\t"	// xmm0 = src1[00, 01, 02, 03]
								  "movaps 10(%%ecx)	,	%%xmm1\n\t"	// xmm1 = src1[04, 05, 06, 07]
								  "movaps 20(%%ecx)	,	%%xmm2\n\t"	// xmm2 = src1[08, 09, 10, 11]
								  "movaps 30(%%ecx) ,	%%xmm3\n\t"	// xmm3 = src1[12, 13, 14, 15]

								  "movaps (%%edx)	,	%%xmm4\n\t"	// xmm4 = src2[00, 01, 02, 03]
								  "movaps 10(%%edx)	,	%%xmm5\n\t"	// xmm5 = src2[04, 05, 06, 07]
								  "movaps 20(%%edx)	,	%%xmm6\n\t"	// xmm6 = src2[08, 09, 10, 11]
								  "movaps 30(%%edx)	,	%%xmm7\n\t"	// xmm7 = src2[12, 13, 14, 15]

								  "addps %%xmm0		,	%%xmm4\n\t"	// xmm4 += xmm0
								  "addps %%xmm1		,	%%xmm5\n\t"	// xmm5 += xmm1
								  "addps %%xmm2		,	%%xmm6\n\t"	// xmm6 += xmm2
								  "addps %%xmm3		,	%%xmm7\n\t"	// xmm7 += xmm3
								  
								  "movaps %%xmm4	,	(%%eax)\n\t"	// eax = xmm4
								  "movaps %%xmm5	,	10(%%eax)\n\t"	// eax = xmm5
								  "movaps %%xmm6	,	20(%%eax)\n\t"	// eax = xmm6
								  "movaps %%xmm7	,	30(%%eax)\n\t"	// eax = xmm7
								  :
								  :"a"(dst), "c"(lhs), "d"(rhs)
								  :"memory");
				
#elif defined (ENO_COMPILED_FROM_VISUAL_STUDIO)
				
				__asm
				{
					mov		eax,	dst
					mov		ecx,	lhs
					mov		edx,	rhs
					
					movaps	xmm0,	xmmword ptr [ecx]		 // xmm0 = src1[00, 01, 02, 03]
					movaps	xmm1,	xmmword ptr [ecx + 0x10] // xmm1 = src1[04, 05, 06, 07]
					movaps	xmm2,	xmmword ptr [ecx + 0x20] // xmm2 = src1[08, 09, 10, 11]
					movaps	xmm3,	xmmword ptr [ecx + 0x30] // xmm3 = src1[12, 13, 14, 15]

					movaps	xmm4,	xmmword ptr [edx]		 // xmm4 = src2[00, 01, 02, 03]
					movaps	xmm5,	xmmword ptr [edx + 0x10] // xmm5 = src2[04, 05, 06, 07]
					movaps	xmm6,	xmmword ptr [edx + 0x20] // xmm6 = src2[08, 09, 10, 11]
					movaps	xmm7,	xmmword ptr [edx + 0x30] // xmm7 = src2[12, 13, 14, 15]
					
					addps	xmm4,	xmm0 // xmm4 += xmm0
					addps	xmm5,	xmm1 // xmm5 += xmm1
					addps	xmm6,	xmm2 // xmm6 += xmm2
					addps	xmm7,	xmm3 // xmm7 += xmm3
					
					movaps	xmmword ptr [eax],			xmm4 // eax = xmm4
					movaps	xmmword ptr [eax + 0x10],	xmm5 // eax = xmm5
					movaps	xmmword ptr [eax + 0x20],	xmm6 // eax = xmm6
					movaps	xmmword ptr [eax + 0x30],	xmm7 // eax = xmm7
				}
#endif				
			}

			template<typename _Ty>
			inline void subMatrixSSE( class_type::matrix4x4_template<_Ty>& out,
									const class_type::matrix4x4_template<_Ty>& a,
									const class_type::matrix4x4_template<_Ty>& b )
			{
				subMatrix(out, a, b);
			}

			template<>
			inline void subMatrixSSE( class_type::matrix4x4_template<f32>& out,
									const class_type::matrix4x4_template<f32>& a,
									const class_type::matrix4x4_template<f32>& b )
			{
				f32 * dst = out.M;
				f32 * lhs = const_cast<f32*>(a.M);
				f32 * rhs = const_cast<f32*>(b.M);

#if defined (ENO_COMPILED_FROM_GNUC)
				asm __volatile__ (
					"movaps (%%ecx)		,	%%xmm0\n\t"	// xmm0 = src1[00, 01, 02, 03]
					"movaps 10(%%ecx)	,	%%xmm1\n\t"	// xmm1 = src1[04, 05, 06, 07]
					"movaps 20(%%ecx)	,	%%xmm2\n\t"	// xmm2 = src1[08, 09, 10, 11]
					"movaps 30(%%ecx)	,	%%xmm3\n\t"	// xmm3 = src1[12, 13, 14, 15]

					"movaps (%%edx)		,	%%xmm4\n\t"	// xmm4 = src2[00, 01, 02, 03]
					"movaps 10(%%edx)	,	%%xmm5\n\t"	// xmm5 = src2[04, 05, 06, 07]
					"movaps 20(%%edx)	,	%%xmm6\n\t"	// xmm6 = src2[08, 09, 10, 11]
					"movaps 30(%%edx)	,	%%xmm7\n\t"	// xmm7 = src2[12, 13, 14, 15]

					"subps %%xmm0		,	%%xmm4\n\t"	// xmm4 -= xmm0
					"subps %%xmm1		,	%%xmm5\n\t"	// xmm5 -= xmm1
					"subps %%xmm2		,	%%xmm6\n\t"	// xmm6 -= xmm2
					"subps %%xmm3		,	%%xmm7\n\t"	// xmm7 -= xmm3

					"movaps %%xmm4	,	(%%eax)\n\t"	// eax = xmm4
					"movaps %%xmm5	,	10(%%eax)\n\t"	// eax = xmm5
					"movaps %%xmm6	,	20(%%eax)\n\t"	// eax = xmm6
					"movaps %%xmm7	,	30(%%eax)\n\t"	// eax = xmm7
					:
					:"a"(dst), "c"(lhs), "d"(rhs)
					:"memory");
#elif defined (ENO_COMPILED_FROM_VISUAL_STUDIO)

				__asm
				{
					mov eax, dst
					mov ecx, lhs
					mov edx, rhs

					movaps xmm0, xmmword ptr [ecx]			// xmm0 = src1[00, 01, 02, 03]
					movaps xmm1, xmmword ptr [ecx + 0x10]	// xmm1 = src1[04, 05, 06, 07]
					movaps xmm2, xmmword ptr [ecx + 0x20]	// xmm2 = src1[08, 09, 10, 11]
					movaps xmm3, xmmword ptr [ecx + 0x30]	// xmm3 = src1[12, 13, 14, 15]

					movaps xmm4, xmmword ptr [edx]			// xmm4 = src2[00, 01, 02, 03]
					movaps xmm5, xmmword ptr [edx + 0x10]	// xmm5 = src2[04, 05, 06, 07]
					movaps xmm6, xmmword ptr [edx + 0x20]	// xmm6 = src2[08, 09, 10, 11]
					movaps xmm7, xmmword ptr [edx + 0x30]	// xmm7 = src2[12, 13, 14, 15]

					subps xmm0, xmm4						// xmm4 -= xmm0
					subps xmm1, xmm5						// xmm5 -= xmm1
					subps xmm2, xmm6						// xmm6 -= xmm2
					subps xmm3, xmm7						// xmm7 -= xmm3

					movaps xmmword ptr [eax]		, xmm0	// eax = xmm4
					movaps xmmword ptr [eax + 0x10]	, xmm1	// eax = xmm5
					movaps xmmword ptr [eax + 0x20]	, xmm2	// eax = xmm6
					movaps xmmword ptr [eax + 0x30]	, xmm3	// eax = xmm7
				}
#endif
			}

			template<typename _Ty>
			inline void addValueMatrixSSE( class_type::matrix4x4_template<_Ty>& out,
										const class_type::matrix4x4_template<_Ty>& a,
										const _Ty value )
			{
				addValueMatrix(out, a, value);
			}

			template<>
			inline void addValueMatrixSSE( class_type::matrix4x4_template<f32>& out, 
										const class_type::matrix4x4_template<f32>& a, 
										const f32 value )
			{
				f32 * dst = out.M;
				f32 * lhs = const_cast<f32*>(a.M);
				f32 * rhv = const_cast<f32*>(&value);

#if defined (ENO_COMPILED_FROM_GNUC)
				asm __volatile__(
								"movaps (%%ecx)  ,	%%xmm0\n\t"	// xmm0 = src1[00, 01, 02, 03]
								"movaps 10(%%ecx),	%%xmm1\n\t"	// xmm1 = src1[04, 05, 06, 07]
								"movaps 20(%%ecx),	%%xmm2\n\t"	// xmm2 = src1[08, 09, 10, 11]
								"movaps 30(%%ecx),	%%xmm3\n\t"	// xmm3 = src1[12, 13, 14, 15]

								"movss	(%%edx)	 ,	%%xmm4\n\t"		// xmm4 = src2[00, xx, xx, xx]
								"shufps $0x0, %%xmm4, %%xmm4\n\t"	// xmm4 = src2[00, 00, 00, 00]

								"addps %%xmm4	 ,	%%xmm0\n\t"
								"addps %%xmm4	 ,	%%xmm1\n\t"
								"addps %%xmm4	 ,	%%xmm2\n\t"
								"addps %%xmm4	 ,	%%xmm3\n\t"

								"movaps %%xmm0	 ,	(%%eax)\n\t"
								"movaps %%xmm1	 ,	10(%%eax)\n\t"
								"movaps %%xmm2	 ,	20(%%eax)\n\t"
								"movaps %%xmm3	 ,	30(%%eax)\n\t"
								:
								:"a"(dst), "c"(lhs), "d"(rhv)
								:"memory");

#elif defined (ENO_COMPILED_FROM_VISUAL_STUDIO)

				__asm {
					mov eax, dst	// eax = dst
					mov ecx, lhs	// ecx = lhs
					mov edx, rhv	// edx = rhv

					movaps xmm0,	xmmword ptr [ecx]
					movaps xmm1,	xmmword ptr [ecx + 0x10]
					movaps xmm2,	xmmword ptr [ecx + 0x20]
					movaps xmm3,	xmmword ptr [ecx + 0x30]

					movss xmm4,		dword ptr [edx]
					shufps xmm4, xmm4, 0x0

					addps xmm0, xmm4
					addps xmm1, xmm4
					addps xmm2, xmm4
					addps xmm3, xmm4

					movaps xmmword ptr [eax]		,	xmm0
					movaps xmmword ptr [eax + 0x10]	,	xmm1
					movaps xmmword ptr [eax + 0x20]	,	xmm2
					movaps xmmword ptr [eax + 0x30]	,	xmm3
				}
#endif
			}

			template<typename _Ty>
			inline void subtractValueMatrixSSE( class_type::matrix4x4_template<_Ty>& out,
				const class_type::matrix4x4_template<_Ty>& a,
				const _Ty value )
			{
				subtractValueMatrix(out, a, value);
			}

			template<>
			inline void subtractValueMatrixSSE( class_type::matrix4x4_template<f32>& out, 
				const class_type::matrix4x4_template<f32>& a, 
				const f32 value )
			{
				f32 * dst = out.M;
				f32 * lhs = const_cast<f32*>(a.M);
				f32 * rhv = const_cast<f32*>(&value);

#if defined (ENO_COMPILED_FROM_GNUC)
				asm __volatile__(
					"movaps (%%ecx)  ,	%%xmm0\n\t"	// xmm0 = src1[00, 01, 02, 03]
					"movaps 10(%%ecx),	%%xmm1\n\t"	// xmm1 = src1[04, 05, 06, 07]
					"movaps 20(%%ecx),	%%xmm2\n\t"	// xmm2 = src1[08, 09, 10, 11]
					"movaps 30(%%ecx),	%%xmm3\n\t"	// xmm3 = src1[12, 13, 14, 15]

					"movss	(%%edx)	 ,	%%xmm4\n\t"		// xmm4 = src2[00, xx, xx, xx]
					"shufps $0x0, %%xmm4, %%xmm4\n\t"	// xmm4 = src2[00, 00, 00, 00]

					"subps %%xmm4	 ,	%%xmm0\n\t"
					"subps %%xmm4	 ,	%%xmm1\n\t"
					"subps %%xmm4	 ,	%%xmm2\n\t"
					"subps %%xmm4	 ,	%%xmm3\n\t"

					"movaps %%xmm0	 ,	(%%eax)\n\t"
					"movaps %%xmm1	 ,	10(%%eax)\n\t"
					"movaps %%xmm2	 ,	20(%%eax)\n\t"
					"movaps %%xmm3	 ,	30(%%eax)\n\t"
					:
					:"a"(dst), "c"(lhs), "d"(rhv)
					:"memory");

#elif defined (ENO_COMPILED_FROM_VISUAL_STUDIO)

				__asm {
					mov eax, dst	// eax = dst
					mov ecx, lhs	// ecx = lhs
					mov edx, rhv	// edx = rhv

					movaps xmm0,	xmmword ptr [ecx]
					movaps xmm1,	xmmword ptr [ecx + 0x10]
					movaps xmm2,	xmmword ptr [ecx + 0x20]
					movaps xmm3,	xmmword ptr [ecx + 0x30]

					movss xmm4,		dword ptr [edx]
					shufps xmm4, xmm4, 0x0

					subps xmm0, xmm4
					subps xmm1, xmm4
					subps xmm2, xmm4
					subps xmm3, xmm4

					movaps xmmword ptr [eax]		,	xmm0
					movaps xmmword ptr [eax + 0x10]	,	xmm1
					movaps xmmword ptr [eax + 0x20]	,	xmm2
					movaps xmmword ptr [eax + 0x30]	,	xmm3
				}
#endif
			}

			template<typename _Ty>
			inline void multiplyValueMatrixSSE( class_type::matrix4x4_template<_Ty>& out,
				const class_type::matrix4x4_template<_Ty>& a,
				const _Ty value )
			{
				multiplyValueMatrix(out, a, value);
			}

			template<>
			inline void multiplyValueMatrixSSE( class_type::matrix4x4_template<f32>& out, 
				const class_type::matrix4x4_template<f32>& a, 
				const f32 value )
			{
				f32 * dst = out.M;
				f32 * lhs = const_cast<f32*>(a.M);
				f32 * rhv = const_cast<f32*>(&value);

#if defined (ENO_COMPILED_FROM_GNUC)
				asm __volatile__(
					"movaps (%%ecx)  ,	%%xmm0\n\t"	// xmm0 = src1[00, 01, 02, 03]
					"movaps 10(%%ecx),	%%xmm1\n\t"	// xmm1 = src1[04, 05, 06, 07]
					"movaps 20(%%ecx),	%%xmm2\n\t"	// xmm2 = src1[08, 09, 10, 11]
					"movaps 30(%%ecx),	%%xmm3\n\t"	// xmm3 = src1[12, 13, 14, 15]

					"movss	(%%edx)	 ,	%%xmm4\n\t"		// xmm4 = src2[00, xx, xx, xx]
					"shufps $0x0, %%xmm4, %%xmm4\n\t"	// xmm4 = src2[00, 00, 00, 00]

					"mulps %%xmm4	 ,	%%xmm0\n\t"
					"mulps %%xmm4	 ,	%%xmm1\n\t"
					"mulps %%xmm4	 ,	%%xmm2\n\t"
					"mulps %%xmm4	 ,	%%xmm3\n\t"

					"movaps %%xmm0	 ,	(%%eax)\n\t"
					"movaps %%xmm1	 ,	10(%%eax)\n\t"
					"movaps %%xmm2	 ,	20(%%eax)\n\t"
					"movaps %%xmm3	 ,	30(%%eax)\n\t"
					:
					:"a"(dst), "c"(lhs), "d"(rhv)
					:"memory");

#elif defined (ENO_COMPILED_FROM_VISUAL_STUDIO)

				__asm {
					mov eax, dst	// eax = dst
					mov ecx, lhs	// ecx = lhs
					mov edx, rhv	// edx = rhv

					movaps xmm0,	xmmword ptr [ecx]
					movaps xmm1,	xmmword ptr [ecx + 0x10]
					movaps xmm2,	xmmword ptr [ecx + 0x20]
					movaps xmm3,	xmmword ptr [ecx + 0x30]

					movss xmm4,		dword ptr [edx]
					shufps xmm4, xmm4, 0x0

					mulps xmm0, xmm4
					mulps xmm1, xmm4
					mulps xmm2, xmm4
					mulps xmm3, xmm4

					movaps xmmword ptr [eax]		,	xmm0
					movaps xmmword ptr [eax + 0x10]	,	xmm1
					movaps xmmword ptr [eax + 0x20]	,	xmm2
					movaps xmmword ptr [eax + 0x30]	,	xmm3
				}
#endif
			}

			template<typename _Ty>
			inline void devideValueMatrixSSE( class_type::matrix4x4_template<_Ty>& out,
				const class_type::matrix4x4_template<_Ty>& a,
				const _Ty value )
			{
				devideValueMatrix(out, a, value);
			}

			template<>
			inline void devideValueMatrixSSE( class_type::matrix4x4_template<f32>& out, 
				const class_type::matrix4x4_template<f32>& a, 
				const f32 value )
			{
				f32 * dst = out.M;
				f32 * lhs = const_cast<f32*>(a.M);
				f32 * rhv = const_cast<f32*>(&value);

#if defined (ENO_COMPILED_FROM_GNUC)
				asm __volatile__(
					"movaps (%%ecx)  ,	%%xmm0\n\t"	// xmm0 = src1[00, 01, 02, 03]
					"movaps 10(%%ecx),	%%xmm1\n\t"	// xmm1 = src1[04, 05, 06, 07]
					"movaps 20(%%ecx),	%%xmm2\n\t"	// xmm2 = src1[08, 09, 10, 11]
					"movaps 30(%%ecx),	%%xmm3\n\t"	// xmm3 = src1[12, 13, 14, 15]

					"movss	(%%edx)	 ,	%%xmm4\n\t"		// xmm4 = src2[00, xx, xx, xx]
					"shufps $0x0, %%xmm4, %%xmm4\n\t"	// xmm4 = src2[00, 00, 00, 00]

					"divps %%xmm4	 ,	%%xmm0\n\t"
					"divps %%xmm4	 ,	%%xmm1\n\t"
					"divps %%xmm4	 ,	%%xmm2\n\t"
					"divps %%xmm4	 ,	%%xmm3\n\t"

					"movaps %%xmm0	 ,	(%%eax)\n\t"
					"movaps %%xmm1	 ,	10(%%eax)\n\t"
					"movaps %%xmm2	 ,	20(%%eax)\n\t"
					"movaps %%xmm3	 ,	30(%%eax)\n\t"
					:
					:"a"(dst), "c"(lhs), "d"(rhv)
					:"memory");

#elif defined (ENO_COMPILED_FROM_VISUAL_STUDIO)

				__asm {
					mov eax, dst	// eax = dst
					mov ecx, lhs	// ecx = lhs
					mov edx, rhv	// edx = rhv

					movaps xmm0,	xmmword ptr [ecx]
					movaps xmm1,	xmmword ptr [ecx + 0x10]
					movaps xmm2,	xmmword ptr [ecx + 0x20]
					movaps xmm3,	xmmword ptr [ecx + 0x30]

					movss xmm4,		dword ptr [edx]
					shufps xmm4, xmm4, 0x0

					divps xmm0, xmm4
					divps xmm1, xmm4
					divps xmm2, xmm4
					divps xmm3, xmm4

					movaps xmmword ptr [eax]		,	xmm0
					movaps xmmword ptr [eax + 0x10]	,	xmm1
					movaps xmmword ptr [eax + 0x20]	,	xmm2
					movaps xmmword ptr [eax + 0x30]	,	xmm3
				}
#endif
			}

		ENO_FUNCTION_END

		ENO_CLASS_TYPE_BEGIN
			
			template<typename _Ty>
			void matrix4x4_template<_Ty>::Multiply(matrix4x4_template & out, const matrix4x4_template & lhs, const matrix4x4_template & rhs)
			{
				function_type::matrixUtil<_Ty>::multiply(out, lhs, rhs);
			}
			
			template<typename _Ty>
			void matrix4x4_template<_Ty>::Add(matrix4x4_template & out, const matrix4x4_template & lhs, const matrix4x4_template & rhs)
			{
				function_type::matrixUtil<_Ty>::add(out, lhs, rhs);
			}

			template<typename _Ty>
			void matrix4x4_template<_Ty>::Subtract( matrix4x4_template & mat, const matrix4x4_template & lhs, const matrix4x4_template & rhs )
			{
				function_type::matrixUtil<_Ty>::subtract(mat, lhs, rhs);
			}

			template<typename _Ty>
			void matrix4x4_template<_Ty>::Add( matrix4x4_template & mat, const matrix4x4_template & lhs, _Ty value )
			{
				function_type::matrixUtil<_Ty>::addValue(mat, lhs, value);
			}

			template<typename _Ty>
			void matrix4x4_template<_Ty>::Subtract( matrix4x4_template & mat, const matrix4x4_template & lhs, _Ty value )
			{
				function_type::matrixUtil<_Ty>::subtractValue(mat, lhs, value);
			}

			template<typename _Ty>
			void matrix4x4_template<_Ty>::Multiply( matrix4x4_template & mat, const matrix4x4_template & lhs, const _Ty value )
			{
				function_type::matrixUtil<_Ty>::multiplyValue(mat, lhs, value);
			}

			template<typename _Ty>
			void matrix4x4_template<_Ty>::Devide( matrix4x4_template & mat, const matrix4x4_template & lhs, const _Ty value )
			{
				function_type::matrixUtil<_Ty>::devideValue(mat, lhs, value);
			}

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// 12 :46 Friday 13 8 2010.

