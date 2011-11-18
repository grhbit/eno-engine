//
//  DriverMACOSX.mm
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 5..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#import "DriverHelperMACOSX.hpp"
#include "DriverMACOSX.hpp"

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            void DriverMAXOSX::createWindow(const enoWindow& window)
            {
                NSApplication* application = [NSApplication sharedApplication];
                
                AppDelegate* appdelegate = [[AppDelegate alloc] init];
                
                [application setDelegate:appdelegate];
                [application run];
                
                [appdelegate release];
                [application release];
            }

            void DriverMAXOSX::destroyWindow(void)
            {
            }

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END