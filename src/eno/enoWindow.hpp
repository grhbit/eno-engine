//
//  enoWindow.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 3..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#include "size2d.hpp"
#include "rectangle.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            class enoWindow {
            public:
                enoWindow(void);

                void loadDefault(void);

                enum WindowStyle 
                {
                    StyleFullScreen = 0x01,
                    StyleWindowed   = 0x02,
                    StyleBorderless = 0x04,
                    StyleFullScreenWindowed = StyleFullScreen|
                                                StyleWindowed|
                                              StyleBorderless, // 0x07
                    StyleMenubarEnable = 0x08,  // in MacOSX
                    
                    StyleMinimized = 0x10,
                    StyleMaximized = 0x20,
                    StyleResizable = 0x40|StyleMaximized,   // 0x06
                    
                    StyleDefault = StyleWindowed|StyleMenubarEnable|StyleMinimized|StyleResizable,  // 0x7A
                };
                
                void setPosition(const core::position2d_template<s32>& position)
                { this->position = position; }
                
                void setSize(const core::size2d_template<s32>& size)
                { this->size = size; }
                
                void setTitle(const String& title)
                { this->title = title; }

                void setStyle(const WindowStyle& style)
                { this->style = style; }

                core::position2d_template<s32> getPosition(void) const
                { return position; }

                core::size2d_template<s32> getSize(void) const
                { return size; }

                String getTitle(void) const
                { return title; }

                WindowStyle getStyle(void) const
                { return style; }

            protected:
            private:
                core::position2d_template<s32> position;
                core::size2d_template<s32> size;
                String title;
                WindowStyle style;
            };

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END