/*
*  rectangle.hpp
*  eno
*
*  Created by seonggwang.gwon on 10. 11. 23..
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
                    _Ty left_, top_, right_, bottom_;
                };

                _Ty v_[4];
            };
        };

        template<typename _Ty>
        class rectangle_template : public Rectangle<_Ty> {
        public:
            rectangle_template( void ) { }

            explicit rectangle_template( const _Ty* src )
            {
                memcpy(this->v_, src, sizeof(this->v_));
            }

            _Ty getWidth( void ) const { return this->right_ - this->left_; }

            _Ty getHeight( void ) const { return this->bottom_ - this->top_; }

            _Ty getArea( void ) const { return getWidth() * getHeight(); }

            position2d_template<_Ty> getDimension2d( void ) const { return position2d_template<_Ty>(getWidth(), getHeight()); }
        };

        typedef rectangle_template<f32> rectangle;

    }
}