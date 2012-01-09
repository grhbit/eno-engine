//
//  enoOSConfig.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 12. 18..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoConfig.hpp"

#if defined(ENO_WINDOWS_PLATFORM)

#define OSUtil OSUtil_Windows
#define Window Window_Windows

#elif defined(ENO_MACOSX_PLATFORM)

#define OSUtil OSUtil_MACOSX
#define Window Window_MACOSX

#endif