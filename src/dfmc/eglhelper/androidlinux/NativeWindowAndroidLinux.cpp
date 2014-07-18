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

#ifdef DFMC_EGL_USE_ANDROID_LINUX
#include "NativeWindowAndroidLinux.hpp"

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <iostream>

#include <ui/FramebufferNativeWindow.h>
//#include "EGLUtils.h"

namespace dfmc {
namespace eglhelper
{
  EGLNativeDisplayType NativeWindowAndroidLinux::Open() { return EGL_DEFAULT_DISPLAY; }
  void NativeWindowAndroidLinux::Close(EGLNativeDisplayType ) {}

  NativeWindowAndroidLinux::NativeWindowAndroidLinux(const EGLNativeDisplayType, const RenderConfig& renderConfig, const EGLDisplay&, const EGLConfig&)
  {
    if( renderConfig.GetWindowMode() != RenderWindowMode::Fullscreen || renderConfig.GetTargetRectangle().Width() != 0 || renderConfig.GetTargetRectangle().Height() != 0)
    {
      std::cout << "WARNING: NativeWindowAndroidLinux only support full-screen mode" << std::endl;
      std::cout.flush();
    }

    mhWindow = android_createDisplaySurface();
  }


  NativeWindowAndroidLinux::~NativeWindowAndroidLinux()
  {
  }

  EGLNativeDisplayType NativeWindowAndroidLinux::GetDisplayType() const
  {
    return EGL_DEFAULT_DISPLAY;
  }

  EGLNativeWindowType NativeWindowAndroidLinux::GetWindowType() const
  {
    return mhWindow;
  }

  bool NativeWindowAndroidLinux::ProcessMessages() const
  {
	  return true;
  }


}}
#endif
