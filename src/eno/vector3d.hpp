/*
 *  vector3.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 14..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoMath.hpp"

ENO_NAMESPACE_BEGIN
	ENO_CORE_NAMESPACE_BEGIN
		ENO_STRUCT_TYPE_BEGIN

#pragma warning(disable : 4201)	//warning: nonstandard extension used : nameless struct/union

			template<typename _Ty>
			struct
#ifdef ENO_COMPILED_FROM_VISUAL_STUDIO
ENO_ALIGNED(16)
#endif
			Vector3d {
			public:
				typedef _Ty element_type;
				typedef _Ty*pointer;

				union {
					struct {
						_Ty x, y, z;
					};
					
					_Ty v[3];

					u8 buffer[sizeof(_Ty) * 3];
				};
			}
#ifdef ENO_COMPILED_FROM_GNUC
ENO_ALIGNED(16)
#endif
;
#pragma warning(default : 4201)

		ENO_STRUCT_TYPE_END
		ENO_CLASS_TYPE_BEGIN

			template<typename _Ty>
			class vector4d_template; 

			template<typename _Ty>
			class matrix4x4_template;

			template<typename _Ty>
			class vector3d_template : public struct_type::Vector3d<_Ty> {
			public:
				explicit vector3d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
				vector3d_template( _Ty _x, _Ty _y, _Ty _z ) { this->x = _x; this->y = _y; this->z = _z; }
				vector3d_template( const vector3d_template& vec ) { this->x = vec.x; this->y = vec.y; this->z = vec.z; }

				_Ty& operator () ( u8 index ) { return this->v[index]; }
				_Ty	operator () ( u8 index ) const { return this->v[index]; }

				operator _Ty* ()	{ return &this->v[0]; }
				operator const _Ty* () const { return &this->v[0]; }

				inline vector3d_template operator + ( const vector3d_template& rhs )
				{
					return vector3d_template( this->x + rhs.x, this->y + rhs.y, this->z + rhs.z );
				}

				inline vector3d_template operator - ( const vector3d_template& rhs )
				{
					return vector3d_template( this->x - rhs.x, this->y - rhs.y, this->z - rhs.z );
				}

				inline vector3d_template operator * ( const vector3d_template& rhs )
				{
					return vector3d_template( this->x * rhs.x, this->y * rhs.y, this->z * rhs.z );
				}

				inline vector3d_template operator / ( const vector3d_template& rhs )
				{
					return vector3d_template( this->x / rhs.x, this->y / rhs.y, this->z / rhs.z );
				}

				inline vector3d_template operator + ( const _Ty value )
				{
					return vector3d_template( this->x + value, this->y + value, this->z + value );
				}

				inline vector3d_template operator - ( const _Ty value )
				{
					return vector3d_template( this->x - value, this->y - value, this->z - value );
				}

				inline vector3d_template operator * ( const _Ty value )
				{
					return vector3d_template( this->x * value, this->y * value, this->z * value );
				}

				inline vector3d_template operator / ( const _Ty value )
				{
					return vector3d_template( this->x / value, this->y / value, this->z / value );
				}

				inline vector3d_template& operator += ( const vector3d_template& rhs )
				{
					return vector3d_template::add(*this, rhs);
				}

				inline vector3d_template& operator -= ( const vector3d_template& rhs )
				{
					return vector3d_template::subtract(rhs);
				}

				inline vector3d_template& operator *= ( const vector3d_template& rhs )
				{
					*this = vector3d_template(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
					return *this;
				}

				inline vector3d_template& operator /= ( const vector3d_template& rhs )
				{
					*this = vector3d_tempalte(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);
					return *this;
				}

				inline vector3d_template& operator += ( const _Ty value )
				{
					*this = vector3d_template(this->x + value, this->y + value, this->z + value);
					return *this;
				}

				inline vector3d_template& operator -= ( const _Ty value )
				{
					*this = vector3d_template(this->x - value, this->y - value, this->z - value);
					return *this;
				}

				inline vector3d_template& operator *= ( const _Ty value )
				{
					return vector3d_template::scale(value);
				}

				inline vector3d_template& operator /= ( const _Ty value )
				{
					*this = vector3d_template(this->x / value, this->y / value, this->z / value);
					return *this;
				}

				inline vector3d_template operator + ( void ) const
				{
					return *this;
				}

				inline vector3d_template operator - ( void ) const
				{
					return vector3d_template::Scale(*this, -1);
				}

				inline vector3d_template& add( const vector3d_template& rhs )
				{
					vector3d_template::Add(*this, *this, rhs);
					return *this;
				}

				inline vector3d_template& add( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template::Add(*this, lhs, rhs);
					return *this;
				}

				inline vector3d_template& subtract( const vector3d_template& rhs )
				{
					vector3d_template::Subtract( *this, *this, rhs );
					return *this;
				}

				inline vector3d_template& subtract( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template::Subtract(*this, lhs, rhs);
					return *this;
				}

				inline vector3d_template& cross( const vector3d_template& rhs )
				{
					vector3d_template::Cross(*this, *this, rhs);
					return *this;
				}

				inline vector3d_template cross( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template::Cross(*this, lhs, rhs);
					return *this;
				}

				inline _Ty dot( const vector3d_template& rhs )
				{
					return vector3d_template::Dot(*this, rhs);
				}

				inline _Ty length( void )
				{
					return vector3d_template::Length(*this);
				}

				inline _Ty lengthSq( void )
				{
					return vector3d_template::Length(*this);
				}

				inline vector3d_template& lerp( const vector3d_template& rhs, ftype percent )
				{
					vector3d_template::Lerp(*this, *this, rhs, percent);
					return *this;
				}

				inline vector3d_template& lerp( const vector3d_template& lhs, const vector3d_template& rhs, ftype percent )
				{
					vector3d_template::lerp(*this, lhs, rhs, percent);
					return *this;
				}

				inline vector3d_template& minimize( const vector3d_template& rhs )
				{
					vector3d_template::Minimize(*this, *this, rhs);
					return *this;
				}

				inline vector3d_template& minimize( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template::Minimize(*this, lhs, rhs);
					return *this;
				}

				inline vector3d_template& maximize( const vector3d_template& rhs )
				{
					vector3d_template::Maximize(*this, *this, rhs);
					return *this;
				}

				inline vector3d_template& maximize( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template::Maximize(*this, lhs, rhs);
					return *this;
				}

				inline vector3d_template& normalize()
				{
					vector3d_template::Normalize(*this, *this);
				}

				inline vector3d_template& normalize( const vector3d_template& vec3 )
				{
					vector3d_template::Normalize(*this, vec3);
				}

				inline vector3d_template& scale( _Ty value )
				{
					vector3d_template::Scale(*this, *this, value);
					return *this;
				}

				inline vector3d_template& scale( const vector3d_template& lhs, _Ty value )
				{
					vector3d_template::Scale(*this, lhs, value);
					return *this;
				}

			//public static
			public:

				static inline void Add( vector3d_template& vec3, const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vec3.x = lhs.x + rhs.x;
					vec3.y = lhs.y + rhs.y;
					vec3.z = lhs.z + rhs.z;
				}

				static inline vector3d_template Add( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template tmp;
					vector3d_template::Add(tmp, lhs, rhs);
					return tmp;
				}

				static inline void BaryCentric( vector3d_template& vec3, 
					const vector3d_template& v1, const vector3d_template& v2, const vector3d_template& v3, _Ty f, _Ty g )
				{
					vec3 = v1 + f * (v2 - v1) + g * (v3 - v1);
				}

				static inline vector3d_template BaryCentric( const vector3d_template& v1, const vector3d_template& v2, 
					const vector3d_template& v3, _Ty f, _Ty g )
				{
					vector3d_template tmp;
					vector3d_template::BaryCentric(tmp, v1, v2, v3, f, g);
					return tmp;
				}

				static inline void CatmullRom( vector3d_template& vec3,
					const vector3d_template& v1, const vector3d_template& v2, const vector3d_template& v3,
					const vector3d_template& v4, _Ty s )
				{
					static matrix4x4_template<_Ty>
											fac(	0,	 1,	  0,   0,
												 -0.5,	 0,	0.5,   0,
													1,-2.5,	  2,-0.5,
												 -0.5, 1.5,-1.5, 0.5 );

					vector4d_template<_Ty> sV( 1, s, s*s, s*s*s );

					matrix4x4_template<_Ty> rhs(	
									v1.x, v1.y, v1.z, v1.w,
									v2.x, v2.y, v2.z, v2.w,
									v3.x, v3.y, v3.z, v3.w,
									v4.x, v4.y, v4.z, v4.w );
					
					// out = sV*fac*rhs
				}

				static inline vector3d_template CatmullRom( const vector3d_template& v1, const vector3d_template& v2, const vector3d_template& v3,
											const vector3d_template& v4, _Ty s )
				{
					vector3d_template tmp;
					vector3d_template::CatmullRom(tmp, v1, v2, v3, v4, s);
					return tmp;
				}

				static inline void Subtract( vector3d_template& vec3, const vector3d_template & lhs, const vector3d_template& rhs )
				{
					vec3.x = lhs.x - rhs.x;
					vec3.y = lhs.y - rhs.y;
					vec3.z = lhs.z - rhs.z;
				}

				static inline vector3d_template Subtract( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template tmp;
					vector3d_template::Subtract(tmp, lhs, rhs);
					return tmp;
				}

				static inline void Cross( vector3d_template& vec3, const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vec3.x = (lhs.y * rhs.z) - (lhs.z * rhs.y);
					vec3.y = (lhs.z * rhs.x) - (lhs.x * rhs.z);
					vec3.z = (lhs.x * rhs.y) - (lhs.y * rhs.x);
				}

				static inline vector3d_template Cross( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template tmp;
					vector3d_template::Cross(tmp, lhs, rhs);
					return tmp;
				}

				static inline _Ty Dot( const vector3d_template& vec3, const vector3d_template& rhs )
				{
					return (vec3.x * rhs.x) + (vec3.y * rhs.y) + (vec3.z * rhs.z);
				}

				static inline _Ty Length( const vector3d_template& vec3 )
				{
					return sqrt(vector3d_template::LengthSq(vec3));
				}

				static inline _Ty LengthSq( const vector3d_template& vec3 )
				{
					return (vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z);
				}

				static inline void Lerp( vector3d_template& vec3, const vector3d_template& lhs, const vector3d_template& rhs, ftype percent )
				{
					vec3 = lhs + (percent * (rhs - lhs));
				}

				static inline vector3d_template Lerp( const vector3d_template& lhs, const vector3d_template& rhs, ftype percent )
				{
					vector3d_template tmp;
					vector3d_template::Lerp(tmp, lhs, rhs, percent);
					return tmp;
				}

				static inline void Minimize( vector3d_template& vec, const vector3d_template& lhs, const vector3d_template &rhs )
				{
					vec.x = min(lhs.x, rhs.x);
					vec.y = min(lhs.y, rhs.y);
					vec.z = min(lhs.z, rhs.z);
				}

				static inline vector3d_template Minimize( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template tmp;
					vector3d_template::Minimize(tmp, lhs, rhs);
					return tmp;
				}

				static inline void Maximize( vector3d_template& vec, const vector3d_template& lhs, const vector3d_template &rhs )
				{
					vec.x = max(lhs.x, rhs.x);
					vec.y = max(lhs.y, rhs.y);
					vec.z = max(lhs.z, rhs.z);
				}

				static inline vector3d_template Maximize( const vector3d_template& lhs, const vector3d_template& rhs )
				{
					vector3d_template tmp;
					vector3d_template::Maximize(tmp, lhs, rhs);
					return tmp;
				}

				static inline void Normalize( vector3d_template& vec3, const vector3d_template& rhs )
				{
					_Ty leng = rhs.lengthSq();

					if (leng != 0)
						leng = sqrt(leng);

					vec3 *= leng;
				}

				static inline vector3d_template Normalize( const vector3d_template& vec3 )
				{
					vector3d_template tmp;
					vector3d_template::Normalize(tmp, vec3);
					return tmp;
				}

				static inline void Scale( vector3d_template& vec, const vector3d_template& lhs, _Ty value )
				{
					vec.x = lhs.x * value;
					vec.y = lhs.y * value;
					vec.z = lhs.z * value;
				}

				static inline vector3d_template Scale( const vector3d_template& lhs, _Ty value )
				{
					vector3d_template tmp;
					vector3d_template::Scale(tmp, lhs, value);
					return tmp;
				}
			};

			typedef vector3d_template<ftype> vector3d;

		ENO_CLASS_TYPE_END
	ENO_CORE_NAMESPACE_END
ENO_NAMESPACE_END
#include "vector2d.hpp"
#include "vector4d.hpp"
#include "matrix4x4.hpp"
// [skop 4:24 pm Saturday. 8.14. 2010. Created.]

