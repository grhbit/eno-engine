/*
*  quaternion.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 8. 22..
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
            _Ty x, y, z, w;
        };

        _Ty q[4];

        u8 buffer[sizeof(_Ty) * 4];
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
    explicit quaternion_template( _Ty* src ) { memcpy( this->v, src, sizeof(this->v) ); }
    quaternion_template( _Ty _x, _Ty _y, _Ty _z, _Ty _w ) { this->x = _x; this->y = _y; this->z = _z; this->w = _w; }
    quaternion_template( const quaternion_template& quat ) { this->x = quat.x; this->y = quat.y; this->z = quat.z; this->w = quat.w; }


    //public static
public:
};

typedef quaternion_template<ftype> quaternion;

}
    }

    // [skop 1:43 pm Sunday. 8.22. 2010. Created.]
