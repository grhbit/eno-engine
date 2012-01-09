/*
 *  main.cpp
 *  eno
 *
 *  Created by Gwon Seong-gwang on 11. 1. 19..
 *  Copyright 2011 g.passcode@gmail.com . All rights reserved.
 *
 */

#include "Unittest++.h"
#include "enoUnitTest.h"
#include "eno.hpp"
#include "enoWindow.hpp"
#include "enoTimer.hpp"
#include "Window_MACOSX.hpp"
#include "enoReferenceCounter.hpp"
#include "enoOSUtil.hpp"
using namespace eno;

int main(int, char *[])
{
    os::enoWindow* window = os::enoWindow::CreateWindow();
    while (1) {
        
    }
    delete window;
    return UnitTest::RunAllTests();
}
