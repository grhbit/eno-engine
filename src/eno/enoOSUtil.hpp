//
//  enoOSUtil.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 10..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoConfig.hpp"
#include "enoReferenceCounter.hpp"

namespace eno {
    

interface enoOSUtil
{
public:
    void init( void );
protected:
    enoOSUtil( void );
public:
    static enoOSUtil* getInstance( void );
    static void release( void );
private:
    static enoOSUtil* instance;                
};

static enoAutoPtr_<enoOSUtil> OS(true, enoOSUtil::getInstance, enoOSUtil::release);


    }
