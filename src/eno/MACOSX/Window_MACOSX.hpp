//
<<<<<<< HEAD
//  Window_MACOSX.hpp
=======
//  WindowMACOSX.hpp
>>>>>>> googlecode/master
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 30..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

<<<<<<< HEAD
#pragma once
#import "enoWindow.hpp"
#import <objc/objc.h>

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            class Window_MACOSX : public enoWindow
            {
            public:
                Window_MACOSX(void);
                /* virtual */ ~Window_MACOSX(void);
            private:
                id context; //OpenGL context
                id delegate; //Window delegate
            };

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END
=======
#ifndef eno_WindowMACOSX_hpp
#define eno_WindowMACOSX_hpp



#endif
>>>>>>> googlecode/master
