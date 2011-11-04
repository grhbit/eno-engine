//
//  enoDriver.h
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoType.h"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_INTERFACE_TYPE_BEGIN

            interface enoDriver
            {
            public:
                virtual ~enoDriver(void) = 0;
            protected:
                /*
                 window create, destroy, clibboard, system message, etc..
                 */
            };

        ENO_INTERFACE_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END