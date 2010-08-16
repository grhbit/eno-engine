/*
 *  matrix4.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include "enoMath.h"
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
				inline explicit matrix4x4_template( _Ty* src ) { memcpy(this->M, src, sizeof(this->M));}
				inline explicit matrix4x4_template( _Ty _11, _Ty _12, _Ty _13, _Ty _14,
								    _Ty _21, _Ty _22, _Ty _23, _Ty _24,
								    _Ty _31, _Ty _32, _Ty _33, _Ty _34,
								    _Ty _41, _Ty _42, _Ty _43, _Ty _44 )
				{
					this->m11 = _11;	this->m12 = _12;	this->m13 = _13;	this->m14 = _14;
					this->m21 = _21;	this->m22 = _22;	this->m23 = _23;	this->m24 = _24;
					this->m31 = _31;	this->m32 = _32;	this->m33 = _33;	this->m34 = _34;
					this->m41 = _41;	this->m42 = _42;	this->m43 = _43;	this->m44 = _44;
				}
				
				inline explicit matrix4x4_template( const matrix4x4_template & rhs )
				{
					this->m11 = rhs.m11;	this->m12 = rhs.m12;	this->m13 = rhs.m13;	this->m14 = rhs.m14;
					this->m21 = rhs.m21;	this->m22 = rhs.m22;	this->m23 = rhs.m23;	this->m24 = rhs.m24;
					this->m31 = rhs.m31;	this->m32 = rhs.m32;	this->m33 = rhs.m33;	this->m34 = rhs.m34;
					this->m41 = rhs.m41;	this->m42 = rhs.m42;	this->m43 = rhs.m43;	this->m44 = rhs.m44;					
				}

				inline explicit matrix4x4_template( InitializeFlag initFlag = INIT_IDENTITY, _Ty fillValue = 0 );
				
				inline matrix4x4_template& identity( void ) { Identity( *this ); return *this; }
				
				inline bool isIdentity( void ) { return IsIdentity( *this ); }
				
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
				
				inline matrix4x4_template& scale( _Ty x, _Ty y, _Ty z ) { return scale(vector3_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& scale( const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template::MakeScale(*this, vec3);
					return *this;
				}
				
				inline matrix4x4_template& rotate( _Ty x, _Ty y, _Ty z ) { return rotate(vector3_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& rotate( const vector3_template<_Ty> & vec3 )
				{
					return *this;
				}
				
				inline matrix4x4_template& translate( _Ty x, _Ty y, _Ty z ) { return translate(vector3_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& translate( const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template::MakeTranslate(*this, vec3);
					return *this;
				}
				
				inline matrix4x4_template& makeScale( _Ty x, _Ty y, _Ty z ) { return makeScale(vector3_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& makeScale( const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template::MakeScale(*this, vec3);
					return *this;
				}
				
				inline matrix4x4_template& makeRotate( ftype x, ftype y, ftype z ) { return makeRotate(vector3_template<ftype>(x, y, z)); }
				
				inline matrix4x4_template& makeRotate( const vector3_template<ftype> & vec3 )
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
				
				inline matrix4x4_template& makeTranslate( _Ty x, _Ty y, _Ty z ) { return makeTranslate(vector3_template<_Ty>(x, y, z)); }
				
				inline matrix4x4_template& makeTranslate( const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template::MakeTranslate(*this, vec3);
					return *this;
				}
				
				_Ty determinant( void )
				{
					return matrix4x4_template::Determinant(*this);
				}
				
				inline matrix4x4_template& inverse( void )
				{
					*this = matrix4x4_template::Inverse(*this);
					return *this;
				}
				
				inline matrix4x4_template& transpose( void )
				{
					matrix4x4_template::Transpose( *this );
					return *this;
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
					matrix4x4_template tmp;
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
				
				inline static void Fill( matrix4x4_template & mat, _Ty fillValue ) { memset( mat.M, fillValue, sizeof(_Ty)*16 ); }
				
				inline static void Multiply( matrix4x4_template & mat, const matrix4x4_template & lhs, const matrix4x4_template & rhs );
				
				inline static matrix4x4_template Multiply( const matrix4x4_template & lhs, const matrix4x4_template & rhs )
				{
					matrix4x4_template tmp;
					matrix4x4_template::Multiply(tmp, lhs, rhs);
					return tmp;
				}
				
				inline static matrix4x4_template Fill( _Ty fillValue )
				{
					matrix4x4_template tmp;
					matrix4x4_template::Fill( tmp, fillValue );
					return tmp;
				}
				
				inline static void MakeScale( matrix4x4_template & mat, const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template::Identity(mat);
					mat.m11 = vec3.x;
					mat.m22 = vec3.y;
					mat.m33 = vec3.z;
				}
				
				inline static matrix4x4_template MakeScale( const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template tmp;
					matrix4x4_template::MakeScale(tmp, vec3);
					return tmp;
				}
				
				inline static void MakeRotateX( matrix4x4_template & mat, ftype value )
				{
					matrix4x4_template::Identity(mat);
					mat.m22 = cos(value);
					mat.m33 = mat.m22;
					
					mat.m32 = sin(value);
					mat.m23 = -mat.m32;
				}

				inline static matrix4x4_template MakeRotateX( ftype value )
				{
					matrix4x4_template tmp;
					matrix4x4_template::MakeRotateX(tmp, value);
					return tmp;
				}
				
				inline static void MakeRotateY( matrix4x4_template & mat, ftype value )
				{
					matrix4x4_template::Identity(mat);
					mat.m11 = cos(value);
					mat.m33 = mat.m11;
					
					mat.m13 = sin(value);
					mat.m31 = -mat.m13;
				}
				
				inline static matrix4x4_template MakeRotateY( ftype value )
				{
					matrix4x4_template tmp;
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
				
				inline static void MakeTranslate( matrix4x4_template & mat, const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template::Identity(mat);
					mat.m41 = vec3.x;
					mat.m42 = vec3.y;
					mat.m43 = vec3.z;
				}
				
				inline static matrix4x4_template MakeTranslate( const vector3_template<_Ty> & vec3 )
				{
					matrix4x4_template tmp;
					matrix4x4_template::MakeTranslate(tmp, vec3);
					return tmp;
				}
				
				inline static _Ty Determinant( const matrix4x4_template & mat );
				
				inline static matrix4x4_template Inverse( const matrix4x4_template & mat );
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
				return	mat.m11*mat.m22*mat.m33*mat.m44-
						mat.m11*mat.m22*mat.m34*mat.m43-
						mat.m11*mat.m32*mat.m23*mat.m44+
						mat.m11*mat.m32*mat.m24*mat.m43+
						mat.m11*mat.m42*mat.m23*mat.m34-
						mat.m11*mat.m42*mat.m24*mat.m33-
						mat.m21*mat.m12*mat.m33*mat.m44+
						mat.m21*mat.m12*mat.m34*mat.m43+
						mat.m21*mat.m32*mat.m13*mat.m44-
						mat.m21*mat.m32*mat.m14*mat.m43-
						mat.m21*mat.m42*mat.m13*mat.m34+
						mat.m21*mat.m42*mat.m14*mat.m33+
						mat.m31*mat.m12*mat.m23*mat.m44-
						mat.m31*mat.m12*mat.m24*mat.m43-
						mat.m31*mat.m22*mat.m13*mat.m44+
						mat.m31*mat.m22*mat.m14*mat.m43+
						mat.m31*mat.m42*mat.m13*mat.m24-
						mat.m31*mat.m42*mat.m14*mat.m23-
						mat.m41*mat.m12*mat.m23*mat.m34+
						mat.m41*mat.m12*mat.m24*mat.m33+
						mat.m41*mat.m22*mat.m13*mat.m34-
						mat.m41*mat.m22*mat.m14*mat.m33-
						mat.m41*mat.m32*mat.m13*mat.m24+
						mat.m41*mat.m32*mat.m14*mat.m23;
			}

			template<typename _Ty>
			matrix4x4_template<_Ty> matrix4x4_template<_Ty>::Inverse( const matrix4x4_template & mat )
			{
				matrix4x4_template ret;
				matrix4x4_template::Identity(ret);

				_Ty Det = matrix4x4_template::Determinant(mat);
								
				_Ty Inv = static_cast<_Ty>(1.0f)/Det;
				
				ret.m11= Inv * ( mat.m22*mat.m33 - mat.m23*mat.m32 );
				ret.m12=-Inv * ( mat.m12*mat.m33 - mat.m13*mat.m32 );
				ret.m13= Inv * ( mat.m12*mat.m23 - mat.m13*mat.m22 );
				ret.m14= 0.0;
				
				ret.m21=-Inv * ( mat.m21*mat.m33 - mat.m23*mat.m31 );
				ret.m22= Inv * ( mat.m11*mat.m33 - mat.m13*mat.m31 );
				ret.m23=-Inv * ( mat.m11*mat.m23 - mat.m13*mat.m21 );
				ret.m24= 0.0;
				
				ret.m31= Inv * ( mat.m21*mat.m32 - mat.m22*mat.m31 );
				ret.m32=-Inv * ( mat.m11*mat.m32 - mat.m12*mat.m31 );
				ret.m33= Inv * ( mat.m11*mat.m22 - mat.m12*mat.m21 );
				ret.m34= 0.0;
				
				ret.m41=-(mat.m41*ret.m11+mat.m42*ret.m21+mat.m43*ret.m31);
				ret.m42=-(mat.m41*ret.m12+mat.m42*ret.m22+mat.m43*ret.m32);
				ret.m43=-(mat.m41*ret.m13+mat.m42*ret.m23+mat.m43*ret.m33);
				ret.m44= 1.0;
			}

			typedef matrix4x4_template<ftype> matrix4x4;

			static const matrix4x4_template<f32> IdentityMatrix( matrix4x4_template<f32>::INIT_IDENTITY );

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
			struct matrixUtil {
				static void (* multiply)( class_type::matrix4x4_template<_Ty>&, 
										 const class_type::matrix4x4_template<_Ty>&, 
										 const class_type::matrix4x4_template<_Ty>& );
			};

			template<typename _Ty>
			void (* matrixUtil<_Ty>::multiply)( class_type::matrix4x4_template<_Ty>& out, 
											   const class_type::matrix4x4_template<_Ty>& first, 
											   const class_type::matrix4x4_template<_Ty>& second ) = multMatrix;

			template<typename _Ty>
			inline void multiplyMatrixSSE( class_type::matrix4x4_template<_Ty>& out, 
								   const class_type::matrix4x4_template<_Ty>& a, 
								   const class_type::matrix4x4_template<_Ty>& b )
			{
				_Ty * dst = out.M;
				_Ty * lhs = a.M;
				_Ty * rhs = b.M;			
				
				__asm
				{
					mov eax dst
					mov ebx lhs
					mov ecx rhs
					
					movaps xmm0 xmmword ptr [ebx]
					movaps xmm1 xmmword ptr [ebx + 0x10]
					movaps xmm2 xmmword ptr [ebx + 0x20]
					movaps xmm3 xmmword ptr [ebx + 0x30]
					
					movaps xmm7 xmmmword ptr [ecx]
					movaps xmm6 xmm7
					movaps xmm5 xmm7
					movaps xmm4 xmm7
					
					shufps xmm7 xmm7 0x0
					shufps xmm6 xmm7 0x55
					shufps xmm5 xmm7 0xaa
					shufps xmm4 xmm7 0xff
					
					mulps xmm7 xmm0
					mulps xmm6 xmm1
					mulps xmm5 xmm2
					mulps xmm4 xmm3
					
					addps xmm6 xmm7
					addps xmm4 xmm5
					addps xmm4 xmm6
					
					movaps xmmword ptr [eax] xmm4
					
					
					movaps xmm7 xmmmword ptr [ecx + 0x10]
					movaps xmm6 xmm7
					movaps xmm5 xmm7
					movaps xmm4 xmm7
					
					shufps xmm7 xmm7 0x0
					shufps xmm6 xmm7 0x55
					shufps xmm5 xmm7 0xaa
					shufps xmm4 xmm7 0xff
					
					mulps xmm7 xmm0
					mulps xmm6 xmm1
					mulps xmm5 xmm2
					mulps xmm4 xmm3
					
					addps xmm6 xmm7
					addps xmm4 xmm5
					addps xmm4 xmm6
					
					movaps xmmword ptr [eax + 0x10] xmm4
	
					
					movaps xmm7 xmmmword ptr [ecx + 0x20]
					movaps xmm6 xmm7
					movaps xmm5 xmm7
					movaps xmm4 xmm7
					
					shufps xmm7 xmm7 0x0
					shufps xmm6 xmm7 0x55
					shufps xmm5 xmm7 0xaa
					shufps xmm4 xmm7 0xff
					
					mulps xmm7 xmm0
					mulps xmm6 xmm1
					mulps xmm5 xmm2
					mulps xmm4 xmm3
					
					addps xmm6 xmm7
					addps xmm4 xmm5
					addps xmm4 xmm6
					
					movaps xmmword ptr [eax + 0x20] xmm4
	
					
					movaps xmm7 xmmmword ptr [ecx + 0x30]
					movaps xmm6 xmm7
					movaps xmm5 xmm7
					movaps xmm4 xmm7
					
					shufps xmm7 xmm7 0x0
					shufps xmm6 xmm7 0x55
					shufps xmm5 xmm7 0xaa
					shufps xmm4 xmm7 0xff
					
					mulps xmm7 xmm0
					mulps xmm6 xmm1
					mulps xmm5 xmm2
					mulps xmm4 xmm3
					
					addps xmm6 xmm7
					addps xmm4 xmm5
					addps xmm4 xmm6
					
					movaps xmmword ptr [eax + 0x30] xmm4
				}
			}

			template<typename _Ty>
			inline void multMatrixSSE( class_type::matrix4x4_template<_Ty>& out, 
							const class_type::matrix4x4_template<_Ty>& a, 
							const class_type::matrix4x4_template<_Ty>& b )
			{				
				if (sizeof(_Ty) != 4)
					return;
				
				multiplyMatrixSSE(out, a, b);
			}

		ENO_FUNCTION_END

		ENO_CLASS_TYPE_BEGIN
			
			template<typename _Ty>
			void matrix4x4_template<_Ty>::Multiply(matrix4x4_template & out, const matrix4x4_template & lhs, const matrix4x4_template & rhs)
			{
				function_type::matrixUtil<_Ty>::multiply(out, lhs, rhs);
			}

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END

// 12 :46 Friday 13 8 2010.

