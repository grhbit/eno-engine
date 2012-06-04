//
//  enoDriver.hpp
//  eno
//
//  Created by seonggwang.gwon on 11. 11. 3..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoType.hpp"
#include "enoWindow.hpp"

namespace eno {
    

interface enoDriver
{
public:
// protected:
    enoDriver(void) { }
    virtual ~enoDriver(void) { }
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


    }