/*
 *  eno.cpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "eno.hpp"
#include "enoDriver.hpp"

ENO_NAMESPACE_BEGIN
    namespace init {
        
        InitializeError checkState(void)
        {
            return None;
        }

        void setCallbackDraw(void(*draw)(f32 delta))
        {
        }
    
        void setCallbackUpdate(boolean(*update)(f32 delta))
        {
        }

    }

    init::InitializeError run(void)
    {
        init::InitializeError error = init::checkState();
        
        if (error == init::None) {
        }
        
        return error;
    }

ENO_NAMESPACE_END