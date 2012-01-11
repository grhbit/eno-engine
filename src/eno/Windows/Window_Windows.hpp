//
//  Window_Windows.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 12. 1. 10..
//  Copyright (c) 2012³â g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoWindow.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            class AppDelegate;

            class Window_Windows : public enoWindow
            {
            public:
                Window_Windows( const enoWindowProperty& );
                /* virtual */ ~Window_Windows( void );
            private:
                AppDelegate* delegate;
            };

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END