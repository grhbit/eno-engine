//
//  DriverHelperMACOSX.hpp
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 5..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#pragma once
#import <Foundation/Foundation.h>

@interface AppDelegate : NSObject<NSWindowDelegate, NSApplicationDelegate>

@property (nonatomic, assign) NSWindow* window;
@property (nonatomic, assign) NSView* view;

-(id)init;
-(void)dealloc;

@end