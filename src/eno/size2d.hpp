/*
*  size2d.hpp
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

        template<typename _Ty>
        class size2d_template : public Vector2d<_Ty> {
        public:
            size2d_template( void ) { }
            explicit size2d_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v_) ); }
            size2d_template( _Ty width, _Ty height ) { this->x_ = width; this->y_ = height; }
            size2d_template( const size2d_template& size ) { this->x_ = size.x_; this->y_ = size.y_; }

            _Ty getWidth( void ) const { return this->x_; }
            _Ty getHeight( void ) const { return this->y_; }

            _Ty getArea( void ) const { return this->x_*this->y_; }
        };

        typedef size2d_template<ftype> size2d;

    }
}