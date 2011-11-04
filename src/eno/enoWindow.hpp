//
//  enoWindow.h
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "size2d.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_STRUCT_TYPE_BEGIN

            struct WindowProperty {
            public:
                core::position2d_template<s32>  winPos;
                    core::size2d_template<s32>  winSize;
                                        String  winTitle;
                                       boolean  windowed;
                
                WindowProperty(void);
            };

        ENO_STRUCT_TYPE_END

        ENO_CLASS_TYPE_BEGIN

            class enoWindow {
            public:
            protected:
                void Create();
                void Destroy();
            private:
                struct_type::WindowProperty property;
            };

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END