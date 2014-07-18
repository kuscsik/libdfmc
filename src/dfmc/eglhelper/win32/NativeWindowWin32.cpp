#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
// ----------------------------------------------------------------------------
// Copyright 2013 DFMC Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------------------------------------------------------

#ifdef _WIN32
#include <iostream>
#include "NativeWindowWin32.hpp"
#include <windows.h>

namespace
{
  void SetClientSize(HWND hwnd, int clientWidth, int clientHeight)
  {
    if (IsWindow(hwnd))
    {
      DWORD dwStyle = GetWindowLongPtr(hwnd, GWL_STYLE);
      DWORD dwExStyle = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
      HMENU menu = GetMenu(hwnd);

      RECT rc = { 0, 0, clientWidth, clientHeight };

      if (!AdjustWindowRectEx(&rc, dwStyle, menu ? TRUE : FALSE, dwExStyle))
        MessageBox(NULL, TEXT("AdjustWindowRectEx Failed!"), TEXT("Error"), MB_OK);
      SetWindowPos(hwnd, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOZORDER | SWP_NOMOVE);
    }
  }

  /*
  * process_window(): This function handles Windows callbacks.
  */
  LRESULT CALLBACK ProcessWindowMessages(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam) 
  {
    switch (uiMsg) 
    {
    case WM_CLOSE:
      PostQuitMessage(0);
      return 0;
    case WM_ACTIVATE:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SIZE:
      return 0;
    }
    return DefWindowProc(hWnd, uiMsg, wParam, lParam);
  }

}

namespace dfmc {
namespace eglhelper
{
  EGLNativeDisplayType NativeWindowWin32::Open() { return EGL_DEFAULT_DISPLAY; }
  void NativeWindowWin32::Close(EGLNativeDisplayType ) {}

  NativeWindowWin32::NativeWindowWin32(const EGLNativeDisplayType, const RenderConfig& renderConfig, const EGLDisplay&, const EGLConfig&)
  {
    if (renderConfig.GetWindowMode() != RenderWindowMode::Window)
    {
      std::cout << "WARNING: NativeWindowWin32 only support window mode" << std::endl;
      std::cout.flush();
    }

    WNDCLASS wc;
    RECT rect;
    HINSTANCE hInstance;

    const Rectangle targetRectangle = renderConfig.GetTargetRectangle();
    rect.left = targetRectangle.Left();
    rect.right = targetRectangle.Right();
    rect.top = targetRectangle.Top();
    rect.bottom = targetRectangle.Bottom();

    hInstance = GetModuleHandle(NULL);

    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = (WNDPROC)ProcessWindowMessages;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = TEXT("OGLES");

    RegisterClass(&wc);

    mhWindow = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, TEXT("OGLES"), TEXT("main"), WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, targetRectangle.Width(), targetRectangle.Height(), NULL, NULL, hInstance, NULL);

    SetClientSize(mhWindow, targetRectangle.Width(), targetRectangle.Height());

    ShowWindow(mhWindow, SW_SHOW);
    SetForegroundWindow(mhWindow);
    SetFocus(mhWindow);
  }


  NativeWindowWin32::~NativeWindowWin32()
  {
  }


  EGLNativeDisplayType NativeWindowWin32::GetDisplayType() const
  {
    return EGL_DEFAULT_DISPLAY;
  }

  EGLNativeWindowType NativeWindowWin32::GetWindowType() const
  {
    return mhWindow;
  }

  bool NativeWindowWin32::ProcessMessages() const
  {
    MSG sMessage;
    bool bQuit = false;
    if(PeekMessage(&sMessage, NULL, 0, 0, PM_REMOVE)) 
    {
      if(sMessage.message == WM_QUIT) 
      {
        bQuit = true;
      } 
      else 
      {
        TranslateMessage(&sMessage);
        DispatchMessage(&sMessage);
      }
    }
    return ! bQuit;
  }


}}
#endif
