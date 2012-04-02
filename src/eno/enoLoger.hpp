//
//  enoLoger.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 12. 1. 13..
//  Copyright (c) 2012 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoReferenceCounter.hpp"

namespace eno {
    

interface enoLoger
{
public:
    virtual void Log(CString message) = 0;
};


    }