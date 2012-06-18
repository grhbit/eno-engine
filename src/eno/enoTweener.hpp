//
//  enoTweener.hpp
//  eno
//
//  Created by seonggwang.gwon on 12. 6. 5..
//  Copyright (c) 2012 g.passcode@gmail.com. All rights reserved.
//

#pragma once
#include <vector>
#include <tuple>

#include "enoType.hpp"
#include "enoGraphicsType.hpp"

namespace eno {
    
    class enoTweener {
    public:
        struct TweenInfo {
            enum TweenType : u32 {  // x = [0, 1], y = (-inf, inf)
                TWEEN_NONE = 0,     // y = floor(x), y = [x]
                TWEEN_LINEAR,       // y = x, (d/dx)y = 1
                TWEEN_ACCELERLATED, // y = x^2, (d/dx)y = 2x
                TWEEN_DEACCELERLATED,   // y = 1-(1-x)^2, (d/dx)y = 2x(1-x)
                TWEEN_SPRING,       // y = 1-(1-t^2)(cos(pi*(n-1)x))
                TweenType_Count,
            } type;
            spriteVertex vertex;
        };
        
                void draw();
        virtual void update(f64 elapseTime);
        
    protected:
        enoTweener();
        ~enoTweener();
        
        virtual void beginDraw() {}
        virtual void drawInternal() {}
        virtual void endDraw() {}

    private:
        typedef std::tuple<TweenInfo, f64> TweenState;
        std::vector<TweenState> tweenstate_list;
        f64 time;
    };    
}