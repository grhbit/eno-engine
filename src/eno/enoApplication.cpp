//
//  enoApplication.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 19..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#include "enoApplication.hpp"

ENO_NAMESPACE_BEGIN
    ENO_CLASS_TYPE_BEGIN

        enoApplication* enoApplication::instance = nullptr;

        enoApplication* enoApplication::sharedApplication(void)
        {
            if (instance == nullptr) {
                instance = new enoApplication;
            }
            
            return instance;
        }

        void enoApplication::release()
        {
            if (instance != nullptr) {
                delete instance;
                instance = nullptr;
            }
        }

        enoApplication::enoApplication(void) : update(nullptr), draw(nullptr) { }

        s32 enoApplication::mainLoop()
        {
            update(0);
            draw(0);
            
            return 0;
        }

        void enoApplication::setCallbackUpdate(CallbackUpdate update)
        {
            this->update = update;
        }

        void enoApplication::setCallbackDraw(CallbackDraw draw) 
        {
            this->draw = draw;
        }


    ENO_CLASS_TYPE_END
ENO_NAMESPACE_END