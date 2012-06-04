/*
*  vector2d.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 8. 22..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/


#pragma once
#include "enoType.hpp"

namespace eno {
    namespace core {

#pragma warning(disable : 4201)	//warning: nonstandard extension used : nameless struct/union

template<typename _Ty>
struct Vector2d {
public:
    typedef _Ty element_type;
    typedef _Ty*pointer;

    union {
        struct {
            _Ty x_, y_;
        };

        _Ty v_[2];

        u8 buffer_[sizeof(_Ty) * 2];
    };
};

#define Position2d Vector2d

#pragma warning(default : 4201)

template<typename _Ty>
class vector2d_template : public Vector2d<_Ty> {
public:
    vector2d_template( void ) { }
    explicit vector2d_template( _Ty* src ) { memcpy( this->v_, src, sizeof(this->v_) ); }
    vector2d_template( _Ty x, _Ty y ) { this->x_ = x; this->y_ = y; }
    vector2d_template( const vector2d_template& vec ) { this->x_ = vec.x_; this->y_ = vec.y_; }

    inline vector2d_template& add( const vector2d_template& rhs )
    {
        vector2d_template::Add(*this, *this, rhs);
        return *this;
    }

    inline vector2d_template& add( const vector2d_template& lhs, const vector2d_template& rhs )
    {
        vector2d_template::Add(*this, lhs, rhs);
        return *this;
    }

    inline vector2d_template& subtract( const vector2d_template& rhs )
    {
        vector2d_template::Subtract(*this, *this, rhs);
        return *this;
    }

    inline vector2d_template& subtract( const vector2d_template& lhs, const vector2d_template& rhs )
    {
        vector2d_template::Subtract(*this, lhs, rhs);
        return *this;
    }

    //public static
public:

    static inline void Add( vector2d_template& vec2, const vector2d_template& lhs, const vector2d_template& rhs )
    {
        vec2.x_ = lhs.x_ + rhs.x_;
        vec2.y_ = lhs.y_ + rhs.y_;
        vec2.z_ = lhs.z_ + rhs.z_;
    }

    static inline vector2d_template Add( const vector2d_template& lhs, const vector2d_template& rhs )
    {
        vector2d_template tmp;
        vector2d_template::Add(tmp, lhs, rhs);
        return tmp;
    }

    static inline void Subtract( vector2d_template& vec2, const vector2d_template& lhs, const vector2d_template& rhs )
    {
        vec2.x_ = lhs.x_ - rhs.x_;
        vec2.y_ = lhs.y_ - rhs.y_;
        vec2.z_ = lhs.z_ - rhs.z_;
    }

    static inline vector2d_template Subtract( const vector2d_template& lhs, const vector2d_template& rhs )
    {
        vector2d_template tmp;
        vector2d_template::Subtract(tmp, lhs, rhs);
        return tmp;
    }
};

typedef vector2d_template<f32> vector2d;

#define position2d_template vector2d_template
#define position2d vector2d

}
    }

    // [skop 1:31 pm Sunday. 8.22. 2010. Created.]
