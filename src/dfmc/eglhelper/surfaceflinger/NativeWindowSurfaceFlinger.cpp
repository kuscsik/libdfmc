#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
// ----------------------------------------------------------------------------
// Copyright 2014 DFMC Authors
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

#ifdef DFMC_EGL_USE_SURFACEFLINGER
#include "NativeWindowSurfaceFlinger.hpp"
#include <iostream>
#include <gui/ISurfaceComposer.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <ui/DisplayInfo.h>

namespace dfmc {
namespace eglhelper
{
  EGLNativeDisplayType NativeWindowSurfaceFlinger::Open() { return EGL_DEFAULT_DISPLAY; }
  void NativeWindowSurfaceFlinger::Close(EGLNativeDisplayType ) {}

  NativeWindowSurfaceFlinger::NativeWindowSurfaceFlinger(const EGLNativeDisplayType, const RenderConfig& renderConfig, const EGLDisplay&, const EGLConfig&)
  {
    if( renderConfig.GetWindowMode() != RenderWindowMode::Fullscreen || renderConfig.GetTargetRectangle().Width() != 0 || renderConfig.GetTargetRectangle().Height() != 0)
    {
      std::cout << "WARNING: NativeWindowSurfaceFlinger only support full-screen mode" << std::endl;
      std::cout.flush();
    }

    using namespace android;
    mSession = new SurfaceComposerClient();

    sp<IBinder> dtoken(SurfaceComposerClient::getBuiltInDisplay(ISurfaceComposer::eDisplayIdMain));
    DisplayInfo dinfo;
    status_t status = SurfaceComposerClient::getDisplayInfo(dtoken, &dinfo);
    if (status)
    {
      exit(-1);
    }

    // create the native surface
    sp<SurfaceControl> control = mSession->createSurface(String8("Solution57"), dinfo.w, dinfo.h, PIXEL_FORMAT_RGB_565);

    SurfaceComposerClient::openGlobalTransaction();
    control->setLayer(0x40000000);
    SurfaceComposerClient::closeGlobalTransaction();


    mFlingerSurfaceControl = control;
    mFlingerSurface = control->getSurface();
    //mWidth = dinfo.w;
    //mHeight = dinfo.h;
  }


  NativeWindowSurfaceFlinger::~NativeWindowSurfaceFlinger()
  {
  }

  EGLNativeDisplayType NativeWindowSurfaceFlinger::GetDisplayType() const
  {
    return EGL_DEFAULT_DISPLAY;
  }

  EGLNativeWindowType NativeWindowSurfaceFlinger::GetWindowType() const
  {
    return mFlingerSurface.get();
  }

  bool NativeWindowSurfaceFlinger::ProcessMessages() const
  {
	return true;
  }


}}
#endif
