//
//  enoWindow.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 23..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#include "enoWindow.hpp"
#include "enoOSConfig.hpp"
#if defined (ENO_MACOSX_DRIVER)
#include "Window_MACOSX.hpp"
#elif defined (ENO_WINDOWS_DRIVER)
#include "Windows/Window_Windows.hpp"
#endif

namespace eno {
    
    enoWindow* enoWindow::instance = nullptr;
    
    enoWindow* enoWindow::getInstance()
    {
        return instance;
    }
    
    void enoWindow::release()
    {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }

    enoWindow* enoWindow::BuildWindow( const enoWindowProperty& property )
    {
        if(instance)
            delete instance;
    
        instance = new Window(property);
        return enoWindow::getInstance();
    }

}
