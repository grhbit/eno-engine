//
//  Window_MACOSX.hpp
//  eno
//
//  Created by seonggwang.gwon on 11. 11. 30..
//  Copyright (c) 2011??g.passcode@gmail.com . All rights reserved.
//

#pragma once
#import "enoWindow.hpp"
#import <objc/objc.h>

namespace eno
{

    class Window_MACOSX : public enoWindow
    {
    public:
        Window_MACOSX(const enoWindowProperty &);
        /* virtual */ ~Window_MACOSX(void);
        
        /* virtual */ void eventLoop( void );
        void Loop();
        void ResizedWindow(f32 width, f32 height);
    private:
        void UpdateWindows();
        
        id context_; //OpenGL context
        id delegate; //Window delegate
        bool isIdle_;
    public:
        enoWindowProperty property_;
    };

}
