//
//  Window_MACOSX.mm
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 30..
//  Copyright (c) 2011??g.passcode@gmail.com . All rights reserved.
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
-(void) applicationDidFinishLaunching:(NSNotification *)notification;
-(void) sendEvent:(NSEvent *)theEvent;

-(void) initWindow;
-(void) closeWindow;
-(void) setParams;
@end

#import "Window_MACOSX.hpp"
#import "size2d.hpp"

eno::core::size2d_template<eno::s32> windowSize;

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
    
    windowSize = eno::core::size2d_template<eno::s32>(size.width, size.height);
    //TODO : inform resize
}

-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}

-(void) applicationDidFinishLaunching:(NSNotification *)notification
{
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    NSEvent* event = [NSEvent otherEventWithType: NSApplicationDefined
                                        location: NSMakePoint(0,0)
                                   modifierFlags: 0
                                       timestamp: 0.0
                                    windowNumber: 0
                                         context: nil
                                         subtype: 0
                                           data1: 0
                                           data2: 0];
    [NSApp postEvent: event atStart: YES];
    [pool release];
}

-(void) sendEvent:(NSEvent *)theEvent
{
    if( [theEvent type] == NSApplicationDefined)
    {
        dynamic_cast<eno::Window_MACOSX*>(eno::enoWindow::getInstance())->Loop();
        NSLog(@"enoNSApplication: sendEvent %@",theEvent);
    }
    
    [super sendEvent:theEvent];
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

- (void) setParams
{
    NSAutoreleasePool* Pool = [[NSAutoreleasePool alloc] init];
	NSRect contentRect = { { 0, 0 }, { 800, 600 } };
    
	[window setContentSize:contentRect.size];
	[window setTitle:[NSString stringWithUTF8String:"Title"]];		
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

namespace eno {
    
            Window_MACOSX::Window_MACOSX(const enoWindowProperty&):context(nil), delegate(nil), isIdle_(true)
            {
                NSAutoreleasePool* Pool = [[NSAutoreleasePool alloc] init];
                
                delegate = [enoNSApplication sharedApplication];
                [delegate performSelectorOnMainThread:@selector(initWindow) withObject:nil waitUntilDone:YES];
                
                NSOpenGLContext* context = createOpenGLContext(Window, 16, 1, 16, nil);

                [delegate performSelectorOnMainThread:@selector(setParams) withObject:nil waitUntilDone:YES];

                [context setView:[static_cast<enoNSApplication*>(delegate)->window contentView]];
                [context update];
                [context makeCurrentContext];
                
                [delegate setDelegate:delegate];
                
                [Pool release];
            }

            Window_MACOSX::~Window_MACOSX(void)
            {
                NSAutoreleasePool* Pool = [[NSAutoreleasePool alloc] init];
                
                [context release];
                [delegate performSelectorOnMainThread:@selector(closeWindow) withObject:nil waitUntilDone:YES];
                [delegate release];
                
                [Pool release];
            }
    
    void Window_MACOSX::eventLoop()
    {
        NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
        NSEvent* event = [NSEvent otherEventWithType: NSApplicationDefined
                                            location: NSMakePoint(0,0)
                                       modifierFlags: 0
                                           timestamp: 0.0
                                        windowNumber: 0
                                             context: nil
                                             subtype: 0
                                               data1: 0
                                               data2: 0];
        UNUSED(event);
        [[NSApplication sharedApplication] run];
        [pool release];
    }
    
    void Window_MACOSX::Loop()
    {
        PollEvents();
        UpdateWindows();
        Idle();
    }
    
    void Window_MACOSX::PollEvents()
    {
        NSEvent* event;
        
        do
        {
            event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantPast] inMode:NSDefaultRunLoopMode dequeue:YES];
            
            [NSApp sendEvent:event];
        } while (event != nil);
    }
    
    void Window_MACOSX::UpdateWindows()
    {
        
    }
    
    void Window_MACOSX::Idle()
    {
        isIdle_ = true;
        NSEvent* event = [NSApp nextEventMatchingMask:NSAnyEventMask untilDate:[NSDate distantFuture] inMode:NSDefaultRunLoopMode dequeue:NO];
        UNUSED(event);
        isIdle_ = false;
    }

}
