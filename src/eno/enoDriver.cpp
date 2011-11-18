//
//  enoDriver.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 18..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#include "enoDriver.hpp"
#include "DriverMACOSX.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_INTERFACE_TYPE_BEGIN

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

        ENO_INTERFACE_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END