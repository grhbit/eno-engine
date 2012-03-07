//
//  enoOSUtil.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 11..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#include "enoOSConfig.hpp"
#include "enoOSUtil.hpp"
#if defined(ENO_MACOSX_DRIVER)
#include "OSUtil_MACOSX.hpp"
#elif defined(ENO_WINDOWS_DRIVER)
#include "Windows/OSUtil_Windows.hpp"
#endif

namespace eno {
    

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


    }
