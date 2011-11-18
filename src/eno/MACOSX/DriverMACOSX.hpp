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

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            class DriverMAXOSX : public os::interface_type::enoDriver
            {
            public:
                /* virtual */ ~DriverMAXOSX(void) {}

            protected:
                /* virtual */ void createWindow(const enoWindow&);
                /* virtual */ void destroyWindow(void);
            };

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END

#endif