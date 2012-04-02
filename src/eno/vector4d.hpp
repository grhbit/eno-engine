/*
*  vector4d.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 8. 22..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/


#pragma once
#include "enoType.hpp"
#include "matrix4x4.hpp"

namespace eno {
    namespace core {

#pragma warning(disable : 4201)	//warning: nonstandard extension used : nameless struct/union

        template<typename _Ty>
        struct
#ifdef ENO_COMPILED_FROM_VISUAL_STUDIO
            ENO_ALIGNED(16)
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
        ENO_ALIGNED(16)
#endif
            ;
#pragma warning(default : 4201)

        template<typename _Ty>
        class vector4d_template : public Vector4d<_Ty> {
        public:
            vector4d_template() { }
            explicit vector4d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
            vector4d_template( _Ty _x, _Ty _y, _Ty _z, _Ty _w ) { this->x = _x; this->y = _y; this->z = _z; this->w = _w; }
            vector4d_template( const vector4d_template& vec ) { this->x = vec.x; this->y = vec.y; this->z = vec.z; this->w = vec.w; }

            inline vector4d_template& add( const vector4d_template& rhs )
            {
                vector4d_template::Add(*this, *this, rhs);
                return *this;
            }

            inline vector4d_template& add( const vector4d_template& lhs, const vector4d_template& rhs )
            {
                vector4d_template::Add(*this, lhs, rhs);
                return *this;
            }

            inline vector4d_template& subtract( const vector4d_template& rhs )
            {
                vector4d_template::Subtract(*this, *this, rhs);
                return *this;
            }

            inline vector4d_template& subtract( const vector4d_template& lhs, const vector4d_template& rhs )
            {
                vector4d_template::Subtract(*this, lhs, rhs);
                return *this;
            }

            inline vector4d_template& cross( const vector4d_template& u, const vector4d_template& v, const vector4d_template& w )
            {
                vector4d_template::Cross(*this, u, v, w);
                return *this;
            }

            //public static

            static inline void Add( vector4d_template& vec4, const vector4d_template& lhs, const vector4d_template& rhs )
            {
                vec4.x = lhs.x + rhs.x;
                vec4.y = lhs.y + rhs.y;
                vec4.z = lhs.z + rhs.z;
                vec4.w = lhs.w + rhs.w;
            }

            static inline vector4d_template Add( const vector4d_template& lhs, const vector4d_template& rhs )
            {
                vector4d_template tmp;
                vector4d_template::Add(tmp, lhs, rhs);
                return tmp;
            }

            static inline void Subtract( vector4d_template& vec4, const vector4d_template& lhs, const vector4d_template& rhs )
            {					
                vec4.x = lhs.x - rhs.x;
                vec4.y = lhs.y - rhs.y;
                vec4.z = lhs.z - rhs.z;
                vec4.w = lhs.w - rhs.w;
            }

            static inline vector4d_template Subtract( const vector4d_template& lhs, const vector4d_template& rhs )
            {
                vector4d_template tmp;
                vector4d_template::Subtract(tmp, lhs, rhs);
                return tmp;
            }

            static inline void Cross( vector4d_template& vec4, const vector4d_template& u, const vector4d_template& v, const vector4d_template& w )
            {
                _Ty a = (v.x * w.y) - (v.y * w.x);
                _Ty b = (v.x * w.z) - (v.z * w.x);
                _Ty c = (v.x * w.w) - (v.w * w.x);
                _Ty d = (v.y * w.z) - (v.z * w.y);
                _Ty e = (v.y * w.w) - (v.w * w.y);
                _Ty f = (v.z * w.w) - (v.w * w.z);

                vec4 = vector4d_template(
                    (f * u.y) - (e * u.z) + (d * u.w),
                    -((f * u.x) - (c * u.z) + (b * u.w)),
                    (e * u.x) - (c * u.y) + (a * u.w),
                    -((d * u.x) - (b * u.y) + (a * u.z)));
            }

            static inline vector4d_template Cross( const vector4d_template& u, const vector4d_template& v, const vector4d_template& w )
            {
                vector4d_template tmp;
                vector4d_template::Cross(tmp, u, v, w);
                return tmp;
            }

        };

        typedef vector4d_template<ftype> vector4d;

    }
}

// [skop 1:21 pm Sunday. 8.22. 2010. Created.]
