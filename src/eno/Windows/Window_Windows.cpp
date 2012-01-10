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
              private:
                  LPTSTR lpszClass;
                  HWND hWnd;
                  HINSTANCE hInstance;

                  static LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
            };

            AppDelegate::AppDelegate( void ) : lpszClass(_T("eno")), hWnd(NULL), hInstance(NULL)
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
                WNDCLASS WndClass;
                
                ZeroMemory(&WndClass, sizeof(WNDCLASS));
                WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
                WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
                WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
                WndClass.hInstance = hInstance;
                WndClass.lpfnWndProc = AppDelegate::WndProc;
                WndClass.lpszClassName = lpszClass;
                WndClass.lpszMenuName = NULL;
                WndClass.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
                RegisterClass(&WndClass);

                hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
                ShowWindow(hWnd,SW_SHOW);
                UpdateWindow(hWnd);
                
                /*
                TODO : Initialize OpenGL
                */

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

                    }
                }
                //*/
            }

            void AppDelegate::closeWindow( void )
            {
                DestroyWindow(hWnd);
            }

            Window_Windows::Window_Windows( void ) : delegate(nullptr)
            {
                delegate = new AppDelegate;
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