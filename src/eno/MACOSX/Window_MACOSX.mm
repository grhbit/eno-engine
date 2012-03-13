//
//  Window_MACOSX.mm
//  eno
//
//  Created by SEONG GWANG GWON on 11. 11. 30..
//  Copyright (c) 2011??g.passcode@gmail.com . All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>

@interface AppDelegate : NSObject<NSWindowDelegate> 
{
@public
    NSWindow* window;
}

-(void) windowDidBecomeKey:(NSNotification *)aNotification;
-(void) windowDidResignKey:(NSNotification *)aNotification;
-(void) windowWillClose:(NSNotification *)aNotification;
-(void) windowDidResize:(NSNotification *)aNotification;

-(void) initWindow;
-(void) closeWindow;
-(void) setParams;
@end

#import "size2d.hpp"
using namespace eno;

core::size2d_template<s32> windowSize;

@implementation AppDelegate

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
    NSSize size = [NSWindow contentRectForFrameRect:[resizedWindow frame] styleMask:NSTitledWindowMask|NSClosableWindowMask|NSResizableWindowMask|NSMiniaturizableWindowMask].size;
    
    windowSize = core::size2d_template<s32>(size.width, size.height);
    //TODO : inform resize
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
static NSOpenGLContext* createOpenGLContext(OpenGLContextType type, s32 colorSize, s32 alphaSize, s32 depthSize, NSOpenGLContext* share)
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
    
    const s32 index = 9;
    
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

#import "Window_MACOSX.hpp"

namespace eno {
    
            Window_MACOSX::Window_MACOSX(const enoWindowProperty&):context(nil), delegate(nil)
            {
                NSAutoreleasePool* Pool = [[NSAutoreleasePool alloc] init];
                
                [NSApplication sharedApplication];
                
                delegate = [[AppDelegate alloc] init];
                [delegate performSelectorOnMainThread:@selector(initWindow) withObject:nil waitUntilDone:YES];
                
                NSOpenGLContext* context = createOpenGLContext(Window, 16, 1, 16, nil);

                [delegate performSelectorOnMainThread:@selector(setParams) withObject:nil waitUntilDone:YES];

                [context setView:[static_cast<AppDelegate*>(delegate)->window contentView]];
                [context update];
                [context makeCurrentContext];
                
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
    
    void loopfunc(void)
    {
        
    }
    
    void Window_MACOSX::eventLoop()
    {
        [[NSApplication sharedApplication] run];
    }

}
