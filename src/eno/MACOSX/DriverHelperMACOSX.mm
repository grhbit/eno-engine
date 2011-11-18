//
//  DriverHelperMACOSX.mm
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 5..
//  Copyright (c) 2011년 g.passcode@gmail.com . All rights reserved.
//

#import "DriverHelperMACOSX.hpp"

@implementation AppDelegate
@synthesize window;
@synthesize view;

-(void)buildMainMenu
{
    NSMenu* mainMenu = [[NSMenu alloc] init];
    
    NSMenuItem* item = [[NSMenuItem alloc] initWithTitle:@"Apple" action:nil keyEquivalent:@""];
    [mainMenu addItem:item];
    
    NSMenu *menu = [[NSMenu alloc] initWithTitle:@"Apple"];
    [item setSubmenu:menu];
    
    NSMenuItem *mi;
    mi = [menu addItemWithTitle:@"Quit" action:@selector(terminate:) keyEquivalent:@"q"];
    [mi setEnabled:YES];
    
    [[NSApplication sharedApplication] setMainMenu:mainMenu];
    
    [item release];
    [menu release];
}

-(id)init
{
    if (self = [super init]) {
        NSRect size = NSMakeRect(0, 0, 800, 600);

        self.window = [[NSWindow alloc] initWithContentRect:size styleMask:NSTitledWindowMask|NSClosableWindowMask|NSMiniaturizableWindowMask backing:NSBackingStoreBuffered defer:NO];

        self.view = [[NSView alloc] initWithFrame:NSMakeRect(0, 0, 800, 600)];
        [[self.window contentView] addSubview:self.view];
        
        [self buildMainMenu];

    }
    
    return self;
}

-(void)dealloc
{
    [self.view release];
    [self.window release];
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [self.window makeKeyAndOrderFront:self];
}

@end