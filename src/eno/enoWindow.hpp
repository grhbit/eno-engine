//
//  enoWindow.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoApplication.hpp"

namespace eno {

interface enoWindow {
    public:
        virtual ~enoWindow(void) { }

        virtual void eventLoop( void ) = 0;
        // [Caution]
        // Until Application quit, doesn't escape.

        virtual void toggleFullScreen( void ) {};
    public:
        static enoWindow* getInstance();
        static void release();
        static enoWindow* BuildWindow( const enoWindowProperty& );

        static enoWindow* instance;
};

}