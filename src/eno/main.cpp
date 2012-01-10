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
using namespace eno;

int main(int, char *[])
{
    os::enoTimer timer;

    while (1)
    {
        std::cout<<timer.delta()<<std::endl;
    }
    

    return UnitTest::RunAllTests();
}
