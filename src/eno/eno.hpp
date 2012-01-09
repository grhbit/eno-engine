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
#include "size2d.hpp"

ENO_NAMESPACE_BEGIN

    namespace init {

        enum InitializeError {
            None = 0x000,
            CallbackUpdate = 0x001,
            CallbackDraw = 0x002,
       };

        u32 checkState(void);

        void setCallbackDraw(void(*draw)(f32 delta));

        void setCallbackUpdate(boolean(*update)(f32 delta));

        namespace window {
            
            void setPosition(const core::position2d_template<s32>&);

            void setSize(const core::size2d_template<s32>&);
            
            void setTitle(const String&);
        }

        using namespace window;
    }

    u32 run(void);

ENO_NAMESPACE_END