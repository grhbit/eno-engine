//
//  enoWindow.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 23..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#include "enoWindow.hpp"
#include "enoOSConfig.hpp"
#include "Window_MACOSX.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_INTERFACE_TYPE_BEGIN

            enoWindow* enoWindow::CreateWindow(void)
            {
                return new Window;
            }

        ENO_INTERFACE_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END