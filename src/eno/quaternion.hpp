/*
*  quaternion.hpp
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
struct
#ifdef ENO_COMPILED_FROM_VISUAL_STUDIO
    ENO_ALIGNED(16)
#endif
Quaternion {
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
class quaternion_template : public Quaternion<_Ty> {
public:
    explicit quaternion_template( _Ty* src ) { memcpy(this->v_, src, sizeof(this->v_)); }
    quaternion_template( _Ty x, _Ty y, _Ty z, _Ty w ) { this->x_ = x; this->y_ = y; this->z_ = z; this->w_ = w; }
    quaternion_template( const quaternion_template& quat ) { this->x_ = quat.x_; this->y_ = quat.y_; this->z_ = quat.z_; this->w_ = quat.w_; }


    //public static
public:
};

typedef quaternion_template<f32> quaternion;

}
    }

    // [skop 1:43 pm Sunday. 8.22. 2010. Created.]
