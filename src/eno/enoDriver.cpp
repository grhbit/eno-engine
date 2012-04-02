//
//  enoDriver.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 18..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#include "enoDriver.hpp"
#ifdef ENO_MACOSX_DRIVER
#include "DriverMACOSX.hpp"
#endif

namespace eno {
    

enoDriver* enoDriver::getInstance(void)
{
    if (instance == nullptr) {
#ifdef ENO_MACOSX_DRIVER
        instance = new DriverMAXOSX;
#endif
    }

    return instance;
}

enoDriver* enoDriver::instance = nullptr;


    }