//
//  Window_MACOSX.mm
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 30..
//  Copyright (c) 2011 g.passcode@gmail.com . All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>

@interface enoNSApplication : NSApplication <NSApplicationDelegate, NSWindowDelegate>
{
@public
    NSWindow* window;
}

-(void) windowDidBecomeKey:(NSNotification *)aNotification;
-(void) windowDidResignKey:(NSNotification *)aNotification;
-(void) windowWillClose:(NSNotification *)aNotification;
-(void) windowDidResize:(NSNotification *)aNotification;
-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;
-(void) sendEvent:(NSEvent *)theEvent;
-(void) run;

-(void) initWindow;
-(void) closeWindow;
-(void) setParams:(NSData *)data;
-(void) buildApplicationMenu;
@end

#import "Window_MACOSX.hpp"
#import "enoTimer.hpp"
#import <OpenGL/GL.h>

@implementation enoNSApplication

-(void) windowDidBecomeKey:(NSNotification *)aNotification
{
    //TODO : When Window has focus
}

-(void) windowDidResignKey:(NSNotification *)aNotification
{
}

-(void) windowWillClose:(NSNotification *)aNotification
{
    //TODO : Quit
}

-(void) windowDidResize:(NSNotification *)aNotification
{
    id resizedWindow = static_cast<NSWindow*>([aNotification object]);
    NSSize size = 
        [NSWindow contentRectForFrameRect:[resizedWindow frame]
                                styleMask:
                        NSTitledWindowMask|
                      NSClosableWindowMask|
                     NSResizableWindowMask|
                NSMiniaturizableWindowMask].size;

    glViewport(0, 0, size.width, size.height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, 0, 100);

    [resizedWindow setContentSize:size];
    
    //TODO : inform resize
    eno::Window_MACOSX* window_ = static_cast<eno::Window_MACOSX *>(eno::enoWindow::getInstance());
    if (window_) {
        window_->ResizedWindow(size.width, size.height);
    }
}

-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

-(void) sendEvent:(NSEvent *)theEvent
{
    [super sendEvent:theEvent];
}

-(void) run
{
    [self finishLaunching];
    _running = YES;
    
    eno::Window_MACOSX* app = static_cast<eno::Window_MACOSX*>(eno::enoWindow::getInstance());
    NSEvent* event;
    do
    {
        event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];
        
        if (event == nil) {
            app->Loop();
        } else {
            [NSApp sendEvent:event];
        }

    } while ([NSApp isRunning]);
    
    [self terminate:self];
}

-(void) initWindow
{
    NSRect size = NSMakeRect(0, 0, 0, 0);
    window = [[NSWindow alloc] initWithContentRect:size styleMask:NSTitledWindowMask|NSClosableWindowMask|NSResizableWindowMask|NSMiniaturizableWindowMask backing:NSBackingStoreBuffered defer:YES];
    
    [window useOptimizedDrawing:YES];
    [window setExcludedFromWindowsMenu:YES];
    [window setReleasedWhenClosed:NO];
    [window setDelegate:self];
}

-(void) closeWindow
{
    [window setDelegate:nil];
    [window close];
    [window release];
}

- (void) setParams:(NSData *)data
{
    NSAutoreleasePool* Pool = [[NSAutoreleasePool alloc] init];
    
    eno::enoWindowProperty property;
    memcpy(&property, [data bytes], [data length]);
    
	NSRect contentRect = { { 0, 0 }, { static_cast<CGFloat>(property.Width), static_cast<CGFloat>(property.Height) } };

	[window setContentSize:contentRect.size];
	[window setTitle:[NSString stringWithUTF8String:property.Title]];		
	[window center];
    @try
    {
        [window orderFrontRegardless];
    }
    @catch (NSException* exception) {
        NSLog(@"%@", [exception description]);
        NSLog(@"%@", [exception reason]);
    }
    
    [Pool release];
}

- (void) buildApplicationMenu
{
    NSMenu* mainMenu = [[NSMenu alloc] initWithTitle:@""];
    NSMenu* appleMenu = [[NSMenu alloc] initWithTitle:@""];
    NSMenu* windowMenu;
    NSString* title;
    NSString* appName = @"eno";
    
    NSMenuItem* menuItem;
    
    title = [@"About " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];

    title = [@"Hide " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];
    
    menuItem = [appleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
    
    [appleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];
    
    menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];

    [mainMenu addItem:menuItem];
    [NSApp setMainMenu:mainMenu];
    [NSApp setMenu:mainMenu];
    [menuItem release];
    
    windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
    
    menuItem = [[NSMenuItem alloc] initWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    [windowMenu addItem:menuItem];
    [menuItem release];
    
    menuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:windowMenu];
    [[NSApp mainMenu] addItem:menuItem];
    [menuItem release];
    
    [NSApp setWindowsMenu:windowMenu];
    
    [windowMenu release];
    [appleMenu release];
    [mainMenu release];
}

@end

enum OpenGLContextType {
    Window,
    FullScreen,
    PixelBuffer,    //Render target to Texture
    };

// same create D3D Device
static NSOpenGLContext* createOpenGLContext(OpenGLContextType type, eno::s32 colorSize, eno::s32 alphaSize, eno::s32 depthSize, NSOpenGLContext* share)
{
    NSOpenGLPixelFormatAttribute attributes[] = 
    {
        NSOpenGLPFAAccelerated, //Hardware-Accelerated
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAMinimumPolicy,
        NSOpenGLPFAColorSize, static_cast<NSOpenGLPixelFormatAttribute>
        (colorSize),
        NSOpenGLPFAAlphaSize, static_cast<NSOpenGLPixelFormatAttribute>
        (alphaSize),
        NSOpenGLPFADepthSize, static_cast<NSOpenGLPixelFormatAttribute>
        (depthSize),
        NSOpenGLPixelFormatAttribute(0),
        NSOpenGLPixelFormatAttribute(0),
        NSOpenGLPixelFormatAttribute(0),
        NSOpenGLPixelFormatAttribute(0),
        NSOpenGLPixelFormatAttribute(0),
    };
    
    const eno::s32 index = 9;
    
    switch (type) {
        case Window:
            attributes[index+0] = NSOpenGLPFAWindow;
            attributes[index+1] = NSOpenGLPFADoubleBuffer;
            break;
        case FullScreen:
            attributes[index+0] = NSOpenGLPFAFullScreen;
            attributes[index+1] = NSOpenGLPFADoubleBuffer;
            attributes[index+2] = NSOpenGLPFAScreenMask;
            attributes[index+3] = NSOpenGLPixelFormatAttribute(CGDisplayIDToOpenGLDisplayMask(kCGDirectMainDisplay));
            break;
        case PixelBuffer:
            attributes[index+0] = NSOpenGLPFAPixelBuffer;
            attributes[index+1] = NSOpenGLPFAOffScreen;
            break;
    }
    
    NSOpenGLPixelFormat* pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes];
    
    if (pixelFormat == nil)
        return nil;
    
    NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:share];
    
    if (context == nil && (!share))
        context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    
    [pixelFormat release];
    
    return context;
}

namespace eno
{    
    Window_MACOSX::Window_MACOSX(const enoWindowProperty& property):context_(nil), delegate(nil), isIdle_(true), property_(property)
    {
        NSAutoreleasePool* Pool = [[NSAutoreleasePool alloc] init];
        
        delegate = [enoNSApplication sharedApplication];
        [delegate performSelectorOnMainThread:@selector(initWindow) withObject:nil waitUntilDone:YES];
        [delegate performSelectorOnMainThread:@selector(buildApplicationMenu) withObject:nil waitUntilDone:YES];
        
        NSOpenGLContext* context = createOpenGLContext(Window, 32, 1, 16, nil);        
        context_ = context;

        NSData* data = [NSData dataWithBytes:&property length:sizeof(enoWindowProperty)];
        [delegate performSelectorOnMainThread:@selector(setParams:) withObject:data waitUntilDone:YES];

        [context setView:[static_cast<enoNSApplication*>(delegate)->window contentView]];
        [context update];
        [context makeCurrentContext];
        
        [delegate setDelegate:delegate];
        
        [Pool release];
    }

    Window_MACOSX::~Window_MACOSX(void)
    {
        NSAutoreleasePool* Pool = [[NSAutoreleasePool alloc] init];
        
        [context_ release];
        [delegate performSelectorOnMainThread:@selector(closeWindow) withObject:nil waitUntilDone:YES];
        [delegate release];
        
        [Pool release];
    }
    
    void Window_MACOSX::eventLoop()
    {
        NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

        [NSApp run];
        
        [pool release];
    }
    
    void Window_MACOSX::Loop()
    {
        while (PollEvents())
        {
            UpdateWindows();
        }
    }
     
    void Window_MACOSX::ResizedWindow(f32 width, f32 height)
    {
        if(context_ != nil)
            [static_cast<NSOpenGLContext *>(context_) update];
    }
    
    void Window_MACOSX::UpdateWindows()
    {
        static enoTimer timer;
        f32 elapse = timer.touch();
        property_.DrawFunc(elapse);
        property_.UpdateFunc(elapse);
        [(NSOpenGLContext*)context_ flushBuffer];
    }
    
    boolean Window_MACOSX::PollEvents()
    {
        NSEvent* event;
        do
        {
            event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];
            [NSApp sendEvent:event];
        } while (event != nil);
        
        return [NSApp isRunning];
    }
}
