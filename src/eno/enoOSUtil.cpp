//
//  enoOSUtil.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 11..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

<<<<<<< HEAD
#include "enoOSConfig.hpp"
#include "enoOSUtil.hpp"
#ifdef ENO_MACOSX_DRIVER
#include "OSUtil_MACOSX.hpp"
#else if ENO_WINDOWS_DRIVER
#include "Windows/OSUtil_Windows.hpp"
#endif

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_INTERFACE_TYPE_BEGIN

            void enoOSUtil::init( void )
            {
            }

            enoOSUtil::enoOSUtil( void )
            {
                init();
            }

            enoOSUtil* enoOSUtil::getInstance( void )
            {
                if (instance == nullptr) {
                    instance = new OSUtil;
                }
    
                return instance;
            }

            void enoOSUtil::release( void )
            {
                if (instance != nullptr) {
                    delete instance;
                    instance = nullptr;
                }
            }

            enoOSUtil* enoOSUtil::instance = nullptr;

        ENO_INTERFACE_TYPE_END
        ENO_FUNCTION_BEGIN

        ENO_FUNCTION_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END
=======
#include <iostream>
>>>>>>> googlecode/master
