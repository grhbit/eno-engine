/*
 *  eno.hpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 10. 8. 13..
 *  Copyright 2010 g.passcode@gmail.com . All rights reserved.
 *
 */

#pragma once
#include "enoConfig.hpp"
#include "enoType.hpp"

ENO_NAMESPACE_BEGIN
    namespace init {

        enum InitializeError {
            None = 0x000,
            UpdateCallback = 0x001,
            DrawCallback = 0x002,
        };
        
        InitializeError checkState(void);
    
        void setCallbackDraw(void(*draw)(f32 delta));

        void setCallbackUpdate(boolean(*update)(f32 delta));

    }

    init::InitializeError run(void);

ENO_NAMESPACE_END