//
//  enoApplication.cpp
//  eno
//
//  Created by seonggwang.gwon on 11. 11. 19..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#include "enoApplication.hpp"
#include "enoWindow.hpp"

namespace eno {

enoAutoPtr_<enoApplication> APP(false, enoApplication::sharedApplication, enoApplication::release);

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

enoApplication::enoApplication(void) : window(nullptr) { }

bool enoApplication::initialize( const enoWindowProperty& property )
{
    window = enoWindow::BuildWindow(property);

    return true;
}

s32 enoApplication::mainLoop()
{
    window->eventLoop();
    return 0;
}

enoApplication::~enoApplication( void )
{
    if (window != nullptr)
        delete window;
}

}
