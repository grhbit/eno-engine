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
#elif defined (ENO_WINDOWS_PLATFORM)
#include <Windows.h>
eno::ftype CONV_SEC = 1.0;    // void enoTimer::SetupTimer(void);

inline eno::s64 getQueryPerformanceCounter(void)
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);

    return static_cast<eno::s64>(li.QuadPart);
}

#endif

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            u64 enoTimer::GetTime(void)
            {
#if defined (ENO_MACOSX_PLATFORM)
                return mach_absolute_time();
#elif defined (ENO_WINDOWS_PLATFORM)
                return getQueryPerformanceCounter();
#endif
            }

            enoTimer::enoTimer(void)
            {
                SetupTimer();
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

            void enoTimer::SetupTimer(void)
            {
#if defined (ENO_WINDOWS_PLATFORM)
                    LARGE_INTEGER li;
                    QueryPerformanceFrequency(&li);

                    CONV_SEC = 1.0/static_cast<eno::ftype>(li.QuadPart);
#endif
            }

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END