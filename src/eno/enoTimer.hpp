//
//  enoTimer.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 20..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoConfig.hpp"
#include "enoType.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            class enoTimer
            {
            public:
                static u64 GetTime(void);
                enoTimer(void);
                
                ftype touch(void);
                ftype delta(void) const;
            private:
                u64 time;
            };

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END