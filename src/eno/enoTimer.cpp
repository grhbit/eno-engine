//
//  enoTimer.cpp
//  eno
//
//  Created by seonggwang.gwon on 11. 11. 20..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#include "enoTimer.hpp"
#include <chrono>

namespace eno {

f64 enoTimer::GetTime(void)
{
    return
        std::chrono::duration<f64>
        (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}

enoTimer::enoTimer(void)
{
    time = enoTimer::GetTime();
}

f64 enoTimer::touch()
{
    f64 ret = enoTimer::GetTime() - time;
    time += ret;
    return ret;
}

f64 enoTimer::delta() const
{
    return enoTimer::GetTime() - time;
}

}
