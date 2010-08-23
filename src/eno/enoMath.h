/*
 *  enoMath.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

#pragma once
#include <cmath>
#include "enoType.h"

ENO_NAMESPACE_BEGIN

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

	ENO_FUNCTION_BEGIN

		inline bool equal( const s32& lhs, const s32& rhs, const s32 error_range = ERROR_RANGE_S32 )
		{
			return ((lhs - error_range) <= rhs) && ((lhs + error_range) >= rhs);
		}

		inline bool equal( const f32& lhs, const f32& rhs, const f32 error_range = ERROR_RANGE_F32 )
		{
			return ((lhs - error_range) <= rhs) && ((lhs + error_range) >= rhs);
		}

		inline bool equal( const f64& lhs, const f64& rhs, const f64 error_range = ERROR_RANGE_F64 )
		{
			return ((lhs - error_range) <= rhs) && ((lhs + error_range) >= rhs);
		}

		inline s32 min( const s32& lhs, const s32& rhs, const s32 error_range = ERROR_RANGE_S32 )
		{
			return equal(lhs, rhs, error_range)? lhs: (lhs<rhs)? lhs:rhs;
		}

		inline f32 min( const f32& lhs, const f32& rhs, const f32 error_range = ERROR_RANGE_F32 )
		{
			return equal(lhs, rhs, error_range)? lhs: (lhs<rhs)? lhs:rhs;
		}

		inline f64 min( const f64& lhs, const f64& rhs, const f64 error_range = ERROR_RANGE_F64 )
		{
			return equal(lhs, rhs, error_range)? lhs: (lhs<rhs)? lhs:rhs;
		}

		inline s32 max( const s32& lhs, const s32& rhs, const s32 error_range = ERROR_RANGE_S32 )
		{
			return equal(lhs, rhs, error_range)? lhs: (lhs>rhs)? lhs:rhs;
		}

		inline f32 max( const f32& lhs, const f32& rhs, const f32 error_range = ERROR_RANGE_F32 )
		{
			return equal(lhs, rhs, error_range)? lhs: (lhs>rhs)? lhs:rhs;
		}

		inline f64 max( const f64& lhs, const f64& rhs, const f64 error_range = ERROR_RANGE_F64 )
		{
			return equal(lhs, rhs, error_range)? lhs: (lhs>rhs)? lhs:rhs;
		}

	ENO_FUNCTION_END

#define MAX(a, b, c) eno::max(eno::max(a, b), c)
#define MIN(a, b, c) eno::min(eno::min(a, b), c)

ENO_NAMESPACE_END

// 12:22 pm. friday. 13. 8. 2010
// 10:35 am. saturday. 14. 8. 2010
// Changed. PI, PI64 Added.
//			RAD2DEG, DEG2RAD Added.
