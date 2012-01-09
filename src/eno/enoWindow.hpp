//
//  enoWindow.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "size2d.hpp"
#include "rectangle.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_INTERFACE_TYPE_BEGIN

            interface enoWindow {
            public:
                virtual ~enoWindow(void) { }
            public:
                static enoWindow* CreateWindow(void);
            };

        ENO_INTERFACE_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END