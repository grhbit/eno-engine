//
//  Window_Windows.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 12. 1. 10..
//  Copyright (c) 2012 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoWindow.hpp"

namespace eno {

    class AppDelegate;

    class Window_Windows : public enoWindow
    {
    public:
        Window_Windows( const enoWindowProperty& );
        /* virtual */ ~Window_Windows( void );

        /* virtual */ void eventLoop( void );

        /* virtual */ void toggleFullScreen( void );
    private:
        AppDelegate* delegate;
    };

    
}