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
    ENO_OS_NAMESPACE_BEGIN
        

            class DriverMAXOSX : public os::enoDriver
            {
            public:
                /* virtual */ ~DriverMAXOSX(void) {}

            protected:
            };

        
    ENO_OS_NAMESPACE_END
}

#endif