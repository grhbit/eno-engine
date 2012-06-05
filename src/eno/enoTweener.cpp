//
//  enoTweener.cpp
//  eno
//
//  Created by seonggwang.gwon on 12. 6. 5..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#include "enoTweener.hpp"

namespace eno {
    
    enoTweener::enoTweener() : time(0)
    { }
    
    void enoTweener::draw()
    {
        this->beginDraw();
        this->drawInternal();
        this->endDraw();
    }
    
    void enoTweener::update(f64 elapseTime)
    {
        time += elapseTime;
        
    }
}