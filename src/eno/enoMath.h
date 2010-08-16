/*
 *  enoMath.h
 *  eno
 *
 *  Created by 권성광 on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com. All rights reserved.
 *
 */

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
								   
ENO_NAMESPACE_END

// 12:22 pm. friday. 13. 8. 2010
// 10:35 am. saturday. 14. 8. 2010
// Changed. PI, PI64 Added.
//			RAD2DEG, DEG2RAD Added.
