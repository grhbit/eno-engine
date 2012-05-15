//
//  enoTimer.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 20..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoConfig.hpp"
#include "enoType.hpp"

namespace eno {

    class enoTimer
    {
    public:
        static f64 GetTime(void);
        enoTimer(void);

        f64 touch(void);
        f64 delta(void) const;
    private:
        f64 time;
        static void SetupTimer(void);
    };

}
