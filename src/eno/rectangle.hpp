/*
*  rectangle.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 11. 23..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include "vector2d.hpp"

namespace eno {
    namespace core {

#pragma warning(disable : 4201)

template<typename _Ty>
struct Rectangle {
public:
    typedef _Ty element_type;
    typedef _Ty*pointer;

    union {
        struct {
            Vector2d<_Ty> point1;
            Vector2d<_Ty> point2;
        };

        struct {
            _Ty left, top, right, bottom;
        };

        _Ty r[4];
    };
};

template<typename _Ty>
class rectangle_template : public Rectangle<_Ty> {
public:
    rectangle_template( void ) { }

    explicit rectangle_template( const _Ty* src )
    {
        memcpy(this->r, src, sizeof(this->r));
    }

    _Ty getWidth( void ) const { return this->right - this->left; }

    _Ty getHeight( void ) const { return this->bottom - this->top; }

    _Ty getArea( void ) const { return getWidth() * getHeight(); }

    position2d_template<_Ty> getDimension2d( void ) const { return position2d_template<_Ty>(getWidth(), getHeight()); }
};

typedef rectangle_template<ftype> rectangle;

}
    }