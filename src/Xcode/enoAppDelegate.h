//
//  enoAppDelegate.h
//  eno
//
//  Created by Gwon Seong-gwang on 10. 8. 13..
//  Copyright 2010 g.passcode@gmail.com . All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface enoAppDelegate : NSObject <NSApplicationDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
