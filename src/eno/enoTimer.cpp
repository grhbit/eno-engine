//
//  enoTimer.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 20..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#include "enoTimer.hpp"

#if defined (ENO_MACOSX_PLATFORM)
#include <mach/mach_time.h>
#define CONV_SEC 0.000000001   //  1e-9
#endif

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            u64 enoTimer::GetTime(void)
            {
#if defined (ENO_MACOSX_PLATFORM)
                return mach_absolute_time();
#endif
            }

            enoTimer::enoTimer(void)
            {
                this->time = enoTimer::GetTime();
            }

            ftype enoTimer::touch()
            {
                u64 ret = enoTimer::GetTime() - time;
                time = ret + time;
                return ret*CONV_SEC;
            }

            ftype enoTimer::delta() const
            {
                return (enoTimer::GetTime() - time)*CONV_SEC;
            }

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END