//
//  enoApplication.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 19..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "enoType.hpp"
#include "enoReferenceCounter.hpp"

namespace eno {

interface enoWindow;

struct enoWindowProperty
{
public:
    typedef bool (*CallbackUpdate)(f32);
    typedef void (*CallbackDraw)(f32);

public:
    f64 Width;
    f64 Height;

    RString Title;
    bool Fullscreen;
    enoWindowProperty* Alternate;

    CallbackUpdate UpdateFunc;
    CallbackDraw DrawFunc;

public:
    enoWindowProperty( void ) :
      Width(800), Height(600),
          Title(""), Fullscreen(false), Alternate(nullptr),
          UpdateFunc(nullptr), DrawFunc(nullptr) { }

      enoWindowProperty( f64 width, f64 height,
          RString title, bool fullscreen,
          CallbackUpdate updatefunc, CallbackDraw drawfunc,
          enoWindowProperty* alternate = nullptr ) :
      Width(width), Height(height),
          Title(title), Fullscreen(fullscreen),
          UpdateFunc(updatefunc), DrawFunc(drawfunc),
          Alternate(alternate) { }
};

class enoApplication {
public:
    static enoApplication* sharedApplication(void);
    static void release();
public:

    bool initialize(const enoWindowProperty&);

    s32 mainLoop(void); 
    // [Caution]
    // Until Application quit, doesn't escape.

private:

    enoWindow* window;

    static enoApplication* instance;

    enoApplication(void);
    ~enoApplication(void);
};

extern enoAutoPtr_<enoApplication> APP;

}
