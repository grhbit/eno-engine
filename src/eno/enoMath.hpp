/*
*  enoMath.hpp
*  eno
*
*  Created by Gwon Seong-gwang on 10. 8. 13..
*  Copyright 2010 g.passcode@gmail.com . All rights reserved.
*
*/

#pragma once
#include <cmath>
#include "enoType.hpp"

namespace eno {

#ifdef PI
#undef PI
#endif

const f32 PI = 3.141592653589793238462f;

const f32 RAD2DEG = 180.0f/PI;

inline const f32 RadianToDegrees( f32 Radian ) { return Radian * RAD2DEG; }

const f32 DEG2RAD = PI/180.0f;

inline const f32 DegreesToRadian( f32 Degrees ) { return Degrees * DEG2RAD; }

#ifdef PI64
#undef PI64
#endif

const f64 PI64 = 3.141592653589793238462643383279;

const f64 RAD2DEG64 = 180.0/PI64;

inline const f64 RadianToDegrees64( f64 Radian ) { return Radian * RAD2DEG64; }

const f64 DEG2RAD64 = PI64/180.0;

inline const f64 DegreesToRadian64( f64 Degrees ) { return Degrees * DEG2RAD64; }

const s32 ERROR_RANGE_S32 = 0;

const f32 ERROR_RANGE_F32 = 0.00001f;

const f64 ERROR_RANGE_F64 = 0.000000001;

template<typename _Ty>
inline bool equals( const _Ty& lhs, const _Ty& rhs, const _Ty error_range = 0 )
{
    return ((lhs - error_range) <= rhs) && ((lhs + error_range) >= rhs);
}

inline bool equal_s32( const s32& lhs, const s32& rhs, const s32 error_range = ERROR_RANGE_S32 )
{
    return ((lhs - error_range) <= rhs) && ((lhs + error_range) >= rhs);
}

inline bool equal_f32( const f32& lhs, const f32& rhs, const f32 error_range = ERROR_RANGE_F32 )
{
    return ((lhs - error_range) <= rhs) && ((lhs + error_range) >= rhs);
}

inline bool equal_f64( const f64& lhs, const f64& rhs, const f64 error_range = ERROR_RANGE_F64 )
{
    return ((lhs - error_range) <= rhs) && ((lhs + error_range) >= rhs);
}

inline s32 min_s32( const s32& lhs, const s32& rhs, const s32 error_range = ERROR_RANGE_S32 )
{
    return equal_s32(lhs, rhs, error_range)? lhs: (lhs<rhs)? lhs:rhs;
}

inline f32 min_f32( const f32& lhs, const f32& rhs, const f32 error_range = ERROR_RANGE_F32 )
{
    return equal_f32(lhs, rhs, error_range)? lhs: (lhs<rhs)? lhs:rhs;
}

inline f64 min_f32( const f64& lhs, const f64& rhs, const f64 error_range = ERROR_RANGE_F64 )
{
    return equal_f64(lhs, rhs, error_range)? lhs: (lhs<rhs)? lhs:rhs;
}

inline s32 max_s32( const s32& lhs, const s32& rhs, const s32 error_range = ERROR_RANGE_S32 )
{
    return equal_s32(lhs, rhs, error_range)? lhs: (lhs>rhs)? lhs:rhs;
}

inline f32 max_f32( const f32& lhs, const f32& rhs, const f32 error_range = ERROR_RANGE_F32 )
{
    return equal_f32(lhs, rhs, error_range)? lhs: (lhs>rhs)? lhs:rhs;
}

inline f64 max_f64( const f64& lhs, const f64& rhs, const f64 error_range = ERROR_RANGE_F64 )
{
    return equal_f64(lhs, rhs, error_range)? lhs: (lhs>rhs)? lhs:rhs;
}

template<typename _Ty>
inline _Ty scale( const _Ty& value, const _Ty& lls, const _Ty& lrs, const _Ty& rls, const _Ty& rrs )
{
    return ((value - lls) * (rrs - rls) / (lrs - lls) + rls);
}

#if !defined(min)
template<typename _Ty>
inline _Ty& min( const _Ty& lhs, const _Ty& rhs )
{
    return (lhs < rhs)? lhs : rhs;
}
#endif

#if !defined(max)
template<typename _Ty>
inline _Ty& max( const _Ty& lhs, const _Ty& rhs )
{
    return (lhs > rhs)? lhs : rhs;
}
#endif

}

    // 12:22 pm. friday. 13. 8. 2010
    // 10:35 am. saturday. 14. 8. 2010
    // Changed. PI, PI64 Added.
    //			RAD2DEG, DEG2RAD Added.
