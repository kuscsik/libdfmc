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

#ifdef FIX_X11 // FIX: incorrect define
#include "NativeNativeWindowX11.hpp"
#include <iostream>
#include <X11/Xlib.h>
#include <EGL/egl.h>

namespace
{
  /* Waits for map notification */
  Bool WaitForMap(Display *d, XEvent *e, char *win_ptr) {
    return (e->type == MapNotify && e->xmap.window == (*((Window*)win_ptr)));
  }

  /* Creates an X window */
  Window CreateWindow(const char *title, int width, int height, Display* display, EGLDisplay sEGLDisplay, EGLConfig FBConfig, Colormap *pColormap, XVisualInfo **ppVisual) 
  {
    XSetWindowAttributes wa;
    XSizeHints sh;
    XEvent e;
    XVisualInfo *visual, template;

    unsigned long mask;
    long screen;

    Colormap colormap;

    int vID, n;

    Window window;

    screen = DefaultScreen(display);
    eglGetConfigAttrib(sEGLDisplay, FBConfig, EGL_NATIVE_VISUAL_ID, &vID);
    template.visualid = vID;
    visual = XGetVisualInfo(display, VisualIDMask, &template, &n);

    if (!visual) {
      printf("Couldn't get X visual info\n");
      exit(-1);
    }

    colormap = XCreateColormap(display, RootWindow(display, screen), visual->visual, AllocNone);

    wa.colormap = colormap;
    wa.background_pixel = 0xFFFFFFFF;
    wa.border_pixel = 0;
    wa.event_mask = StructureNotifyMask | ExposureMask;

    mask = CWBackPixel | CWBorderPixel | CWEventMask | CWColormap;

    window = XCreateWindow(display, RootWindow(display, screen), 0, 0, width, height, 0, visual->depth, InputOutput, visual->visual, mask, &wa);

    sh.flags = USPosition;
    sh.x = 10;
    sh.y = 10;

    XSetStandardProperties(display, window, title, title, None, 0, 0, &sh);
    XMapWindow(display, window);
    XIfEvent(display, &e, WaitForMap, (char*)&window);
    XSetWMColormapWindows(display, window, &window, 1);
    XFlush(display);

    *pColormap = colormap;
    *ppVisual = visual;

    return window;
  }
}


namespace dfmc {
namespace eglhelper
{

  EGLNativeDisplayType NativeWindowX11::Open()
  {
    EGLNativeDisplayType hDisplay = XOpenDisplay(NULL);

    if (!hDisplay) {
      printf("Could not open display\n");
      exit(-1);
    }
    return hDisplay;
  }

  void NativeWindowX11::Close(EGLNativeDisplayType  hDisplay)
  {
    XCloseDisplay(hDisplay);
  }

  NativeWindowX11::NativeWindowX11(const EGLNativeDisplayType hDisplay, const RenderConfig& renderConfig, const EGLDisplay& eglDisplay, const EGLConfig& config)
    : mhDisplay(hDisplay)
  {
    if( renderConfig.GetWindowMode() != RenderWindowMode::Window )
    {
      std::cout << "WARNING: NativeWindowX11 only support window mode" << std::endl;
      std::cout.flush();
    }

    const Rectangle targetRectangle = renderConfig.GetTargetRectangle();
    mhWindow = CreateWindow("dfmc", targetRectangle.Width(), targetRectangle.Height(), mhDisplay, sEGLDisplay, aEGLConfigs[0], &colormap, &pVisual);

    XSelectInput(hDisplay, mhWindow, KeyPressMask | ExposureMask | EnterWindowMask
      | LeaveWindowMask | PointerMotionMask | VisibilityChangeMask | ButtonPressMask
      | ButtonReleaseMask | StructureNotifyMask);
  }

  NativeWindowX11::~NativeWindowX11()
  {
    /* X windows clean up */
    XDestroyWindow(hDisplay, hWindow);
    XFreeColormap(hDisplay, colormap);
    XFree(pVisual);
  }



  EGLNativeDisplayType NativeWindowX11::GetNativeDisplayType() const
  {
    return mhDisplay;
  }

  EGLNativeWindowType NativeWindowX11::GetWindowType() const
  {
    return mhWindow;
  }

  bool NativeWindowX11::ProcessMessages() const
  {
    bool bQuit = false;
    while (XPending(hDisplay) > 0) 
    {
      XNextEvent(hDisplay, &e);

      if (e.type == ButtonPress) 
      {
        bQuit = true;
      }
    }
    return !bQuit;
  }


}}
#endif
