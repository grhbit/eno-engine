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
#include "enoApplication.hpp"
#include "enoWindow.hpp"

ENO_NAMESPACE_BEGIN
    namespace init {
        
        u32 checkState(void)
        {
            u32 state = None;
            enoApplication* app = enoApplication::sharedApplication();
            
            if (app->getCallbackUpdate() == nullptr)
                state |= CallbackUpdate;
            
            if (app->getCallbackDraw() == nullptr)
                state |= CallbackDraw;
            
            return state;
        }

        void setCallbackDraw(void(*draw)(f32 delta))
        {
            enoApplication::sharedApplication()->setCallbackDraw(draw);
        }

        void setCallbackUpdate(boolean(*update)(f32 delta))
        {
            enoApplication::sharedApplication()->setCallbackUpdate(update);
        }
    }

    u32 run(void)
    {
        u32 error = init::checkState();
        
        if (error == init::None) {
            
            enoApplication::sharedApplication()->mainLoop();
        }
        
        return error;
    }

ENO_NAMESPACE_END