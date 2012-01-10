//
//  enoWindow.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 23..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#include "enoWindow.hpp"
#include "enoOSConfig.hpp"
#if defined (ENO_MACOSX_DRIVER)
#include "Window_MACOSX.hpp"
#elif defined (ENO_WINDOWS_DRIVER)
#include "Windows/Window_Windows.hpp"
#endif

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