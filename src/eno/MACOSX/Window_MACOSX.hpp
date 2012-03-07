//
//  Window_MACOSX.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 30..
//  Copyright (c) 2011??g.passcode@gmail.com . All rights reserved.
//

#pragma once
#import "enoWindow.hpp"
#import <objc/objc.h>

namespace eno {
    ENO_OS_NAMESPACE_BEGIN
        

            class Window_MACOSX : public enoWindow
            {
            public:
                Window_MACOSX(const enoWindowProperty &);
                /* virtual */ ~Window_MACOSX(void);
                
                /* virtual */ void eventLoop( void ) { }
            private:
                id context; //OpenGL context
                id delegate; //Window delegate
            };

        
    ENO_OS_NAMESPACE_END
}
