//
//  enoWindow.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#include "enoWindow.hpp"
#include "enoDriver.h"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_STRUCT_TYPE_BEGIN

            WindowProperty::WindowProperty(void) : winPos(0, 0), winSize(640, 480), winTitle(""), windowed(true)
            { }

        ENO_STRUCT_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END