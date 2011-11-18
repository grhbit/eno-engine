//
//  enoDriver.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoType.hpp"
#include "enoWindow.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_INTERFACE_TYPE_BEGIN

            interface enoDriver
            {
            public:
            protected:
                enoDriver(void) { }
                virtual ~enoDriver(void) { }
                virtual void createWindow(const enoWindow&) = 0;
                virtual void destroyWindow(void) = 0;
            private:
                static enoDriver* instance;
            public:
                static enoDriver* getInstance(void);
                
                static void release(void)
                {
                    if (instance != nullptr) {
                        delete instance;
                        instance = nullptr;
                    }
                }
            };

        ENO_INTERFACE_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END