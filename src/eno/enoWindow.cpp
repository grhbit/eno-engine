//
//  enoWindow.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#include "enoWindow.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            enoWindow::enoWindow(void)
            {
                loadDefault();
            }

            void enoWindow::loadDefault(void)
            {
                position = core::position2d_template<s32>(0, 0);
                size = core::size2d_template<s32>(800, 600);
                title = "";
                style = StyleDefault;
            }

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END