//
//  DriverMACOSX.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 5..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoDriver.hpp"

#ifdef ENO_MACOSX_DRIVER

namespace eno {

            class DriverMAXOSX : public enoDriver
            {
            public:
                /* virtual */ ~DriverMAXOSX(void) {}

            protected:
            };

}

#endif