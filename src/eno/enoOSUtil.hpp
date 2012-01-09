//
//  enoOSUtil.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 10..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoConfig.hpp"
#include "enoReferenceCounter.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_INTERFACE_TYPE_BEGIN

            interface enoOSUtil
            {
            public:
                void init( void );
            private:
                enoOSUtil( void );
            public:
                static enoOSUtil* getInstance( void );
                static void release( void );
            private:
                static enoOSUtil* instance;                
            };

static enoAutoPtr_<enoOSUtil> OS(true, enoOSUtil::getInstance, enoOSUtil::release);

        ENO_INTERFACE_TYPE_END
        ENO_FUNCTION_BEGIN
        ENO_FUNCTION_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END