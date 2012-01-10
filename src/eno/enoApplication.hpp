//
//  enoApplication.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 19..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

<<<<<<< HEAD
#pragma once
#include "enoType.hpp"
#include "enoWindow.hpp"

ENO_NAMESPACE_BEGIN
    ENO_CLASS_TYPE_BEGIN

        class enoApplication {
        public:
            static enoApplication* sharedApplication(void);
            static void release();
        public:
            typedef boolean (*CallbackUpdate)(f32);
            typedef void    (*CallbackDraw)(f32);
            
            s32 mainLoop(void); 
            //[Caution]
            // Until Application quit, doesn't escape.
            
            void setCallbackUpdate(CallbackUpdate);
            CallbackUpdate getCallbackUpdate(void) const { return update; }
            
            void setCallbackDraw(CallbackDraw);
            CallbackDraw getCallbackDraw(void) const { return draw; }
            
        private:
            CallbackUpdate update;
            CallbackDraw   draw;
            
            static enoApplication* instance;
            
            enoApplication(void);
        };

    ENO_CLASS_TYPE_END
ENO_NAMESPACE_END
=======
#ifndef eno_enoApplication_hpp
#define eno_enoApplication_hpp



#endif
>>>>>>> googlecode/master
