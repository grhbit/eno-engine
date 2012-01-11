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
#include "enoApplication.hpp"
#include "enoWindow.hpp"
#include "enoTimer.hpp"
using namespace eno;

int main(int, char *[])
{
    enoWindowProperty property;
    property.Width = 800;
    property.Height = 600;
    os::enoWindow* window = os::enoWindow::BuildWindow(property);


    delete window;
    return UnitTest::RunAllTests();
}
