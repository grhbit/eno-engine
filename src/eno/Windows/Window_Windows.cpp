//
//  Window_Windows.cpp
//  eno
//
//  Created by SEONG GWANG GWON on 12. 1. 10..
//  Copyright (c) 2012³â g.passcode@gmail.com . All rights reserved.
//

#include "Window_Windows.hpp"
#include <Windows.h>
#include <tchar.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

ENO_NAMESPACE_BEGIN
    ENO_OS_NAMESPACE_BEGIN
        ENO_CLASS_TYPE_BEGIN

            class AppDelegate
            {
            public:
                AppDelegate( void );

                ~AppDelegate( void );

                void initWindow( void );
                void closeWindow( void );

                void setWindowProperty( const enoWindowProperty& );
              private:
                  LPTSTR lpszClass;
                  HWND hWnd;
                  HDC hDC;
                  HGLRC hRC;
                  HINSTANCE hInstance;
                  enoWindowProperty Property;

                  static LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
            };

            AppDelegate::AppDelegate( void ) : lpszClass(_T("eno")), hWnd(NULL), hDC(NULL), hRC(NULL), hInstance(NULL)
            {
            }

            AppDelegate::~AppDelegate( void )
            {
            }

            LRESULT AppDelegate::WndProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
            {
                switch(iMessage)
                {
                case WM_DESTROY:
                    PostQuitMessage(0);
                    return 0;
                }

                return (DefWindowProc(hWnd, iMessage, wParam, lParam));
            }

            void AppDelegate::initWindow( void )
            {
                hInstance = GetModuleHandle(NULL);

                RECT rect = { 0, 0, Property.Width, Property.Height };
                DWORD dwStyle = 0;
                DWORD dwExStyle = 0;

                WNDCLASS WndClass;
                ZeroMemory(&WndClass, sizeof(WNDCLASS));
                WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
                WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
                WndClass.hInstance = hInstance;
                WndClass.lpfnWndProc = AppDelegate::WndProc;
                WndClass.lpszClassName = lpszClass;
                WndClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
                RegisterClass(&WndClass);

                if (Property.Fullscreen)
                {
                    DEVMODE dmScreenSettings;
                    ZeroMemory(&dmScreenSettings, sizeof(DEVMODE));

                    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
                    dmScreenSettings.dmPelsWidth = Property.Width;
                    dmScreenSettings.dmPelsHeight = Property.Height;
                    dmScreenSettings.dmBitsPerPel = 32;
                    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PAPERWIDTH | DM_PELSHEIGHT;

                    if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
                        Property.Fullscreen = false;
                    else
                    {
                        dwExStyle = WS_EX_APPWINDOW;
                        dwStyle = WS_POPUP;
                        ShowCursor(FALSE);
                    }
                }
                else
                {
                    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
                    dwStyle = WS_OVERLAPPEDWINDOW;
                }

                AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);
                

                hWnd = CreateWindowEx(dwExStyle, lpszClass, Property.Title.c_str(),
                    dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                    0, 0,
                    rect.right - rect.left, rect.bottom - rect.top,
                    NULL, NULL, hInstance, NULL);

                static PIXELFORMATDESCRIPTOR pfd = 
                {
                    sizeof(PIXELFORMATDESCRIPTOR),
                    1,
                    PFD_DRAW_TO_WINDOW |
                    PFD_SUPPORT_OPENGL |
                    PFD_DOUBLEBUFFER,
                    PFD_TYPE_RGBA,
                    32,
                    0, 0, 0, 0, 0, 0,
                    0,
                    0,
                    0,
                    0, 0, 0, 0,
                    32,
                    0,
                    0,
                    PFD_MAIN_PLANE,
                    0,
                    0, 0, 0
                };

                GLuint PixelFormat = 0;
                hDC = GetDC(hWnd);
                PixelFormat = ChoosePixelFormat(hDC, &pfd);
                SetPixelFormat(hDC, PixelFormat, &pfd);
                hRC = wglCreateContext(hDC);
                wglMakeCurrent(hDC, hRC);

                ShowWindow(hWnd,SW_SHOW);
                SetForegroundWindow(hWnd);
                SetFocus(hWnd);
                UpdateWindow(hWnd);

                glViewport(0,0,Property.Width,Property.Height); 
                glMatrixMode(GL_PROJECTION);  
                glLoadIdentity();
                gluPerspective(45.0f,(GLfloat)Property.Width/(GLfloat)Property.Height,0.1f,100.0f);
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();         


                glShadeModel(GL_SMOOTH);  
                glEnable(GL_DEPTH_TEST);  
                glDepthFunc(GL_LEQUAL);   
                glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

                glClearColor(0.0, 0.3f, 0.5f, 0.5f);
                glClearDepth(1.0f);

                //*// Temp Code, Event Loop
                MSG message;
                ZeroMemory(&message, sizeof(MSG));
                while (true)
                {
                    if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
                    {
                        if(message.message == WM_QUIT) break;

                        TranslateMessage(&message);
                        DispatchMessage(&message);
                    }
                    else
                    {
                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        SwapBuffers(hDC);
                    }
                }
                //*/
            }

            void AppDelegate::closeWindow( void )
            {
                if (hRC != NULL)
                {
                    wglMakeCurrent(NULL, NULL);
                    wglDeleteContext(hRC);
                    hRC = NULL;
                }

                if (hDC != NULL)
                {
                    ReleaseDC(hWnd, hDC);
                    hDC = NULL;
                }

                if (hWnd != NULL)
                {
                    DestroyWindow(hWnd);
                    hWnd = NULL;
                }

                if (hInstance != NULL)
                {
                    UnregisterClass(lpszClass, hInstance);
                    hInstance = NULL;
                }
            }

            void AppDelegate::setWindowProperty( const enoWindowProperty& property )
            {
                Property = property;
            }

            Window_Windows::Window_Windows( const enoWindowProperty& property ) : delegate(nullptr)
            {
                delegate = new AppDelegate;
                delegate->setWindowProperty(property);
                delegate->initWindow();
            }

            Window_Windows::~Window_Windows( void )
            {
                if (delegate != nullptr)
                {
                    delegate->closeWindow();
                    delete delegate;
                }
            }

        ENO_CLASS_TYPE_END
    ENO_OS_NAMESPACE_END
ENO_NAMESPACE_END