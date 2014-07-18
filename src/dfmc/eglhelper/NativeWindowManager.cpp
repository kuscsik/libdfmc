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

#include <dfmc/eglhelper/NativeWindowManager.hpp>

#ifdef _WIN32
#include "win32/NativeWindowWin32.hpp"
#define NATIVEWINDOW NativeWindowWin32
#elif defined(DFMC_EGL_USE_SURFACEFLINGER)
#include "surfaceflinger/NativeWindowSurfaceFlinger.hpp"
#define NATIVEWINDOW NativeWindowSurfaceFlinger
#elif defined(DFMC_EGL_USE_ANDROID_LINUX)
#include "androidlinux/NativeWindowAndroidLinux.hpp"
#define NATIVEWINDOW NativeWindowAndroidLinux
#elif defined(FIX_X11)
#include "x11/NativeWindowX11.hpp"
#define NATIVEWINDOW NativeWindowX11
#elif defined(EGL_API_DFB)
#include "directfb/NativeWindowDirectFB.hpp"
#define NATIVEWINDOW NativeWindowDirectFB
#else
#error Unsupported platform
#endif

namespace dfmc {
namespace eglhelper
{
  NativeWindowManager::NativeWindowManager()
    : mhDisplay(NATIVEWINDOW::Open())
  {
  }

  NativeWindowManager::~NativeWindowManager()
  {
    NATIVEWINDOW::Close(mhDisplay);
  }

  EGLNativeDisplayType NativeWindowManager::GetDisplayType() const
  {
    return mhDisplay;
  }


  INativeWindow* NativeWindowManager::CreateNativeWindow(const RenderConfig& renderConfig, const EGLDisplay& eglDisplay, const EGLConfig& config)
  {
    return new NATIVEWINDOW(mhDisplay, renderConfig, eglDisplay, config);
  }

}}
