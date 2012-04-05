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
                    _Ty x_, y_, z_, w_;
                };

                _Ty v_[4];

                u8 buffer_[sizeof(_Ty) * 4];
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
            explicit vector4d_template( _Ty* src ) { memcpy( this->v_, src, sizeof(this->v_) ); }
            vector4d_template( _Ty x, _Ty y, _Ty z, _Ty w ) { this->x_ = x; this->y_ = y; this->z_ = z; this->w_ = w; }
            vector4d_template( const vector4d_template& vec ) { this->x_ = vec.x_; this->y_ = vec.y_; this->z_ = vec.z_; this->w_ = vec.w_; }

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
                vec4.x_ = lhs.x_ + rhs.x_;
                vec4.y_ = lhs.y_ + rhs.y_;
                vec4.z_ = lhs.z_ + rhs.z_;
                vec4.w_ = lhs.w_ + rhs.w_;
            }

            static inline vector4d_template Add( const vector4d_template& lhs, const vector4d_template& rhs )
            {
                vector4d_template tmp;
                vector4d_template::Add(tmp, lhs, rhs);
                return tmp;
            }

            static inline void Subtract( vector4d_template& vec4, const vector4d_template& lhs, const vector4d_template& rhs )
            {					
                vec4.x_ = lhs.x_ - rhs.x_;
                vec4.y_ = lhs.y_ - rhs.y_;
                vec4.z_ = lhs.z_ - rhs.z_;
                vec4.w_ = lhs.w_ - rhs.w_;
            }

            static inline vector4d_template Subtract( const vector4d_template& lhs, const vector4d_template& rhs )
            {
                vector4d_template tmp;
                vector4d_template::Subtract(tmp, lhs, rhs);
                return tmp;
            }

            static inline void Cross( vector4d_template& vec4, const vector4d_template& u, const vector4d_template& v, const vector4d_template& w )
            {
                _Ty a = (v.x_ * w.y_) - (v.y_ * w.x_);
                _Ty b = (v.x_ * w.z_) - (v.z_ * w.x_);
                _Ty c = (v.x_ * w.w_) - (v.w_ * w.x_);
                _Ty d = (v.y_ * w.z_) - (v.z_ * w.y_);
                _Ty e = (v.y_ * w.w_) - (v.w_ * w.y_);
                _Ty f = (v.z_ * w.w_) - (v.w_ * w.z_);

                vec4 = vector4d_template(
                    (f * u.y_) - (e * u.z_) + (d * u.w_),
                    -((f * u.x_) - (c * u.z_) + (b * u.w_)),
                    (e * u.x_) - (c * u.y_) + (a * u.w_),
                    -((d * u.x_) - (b * u.y_) + (a * u.z_)));
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
