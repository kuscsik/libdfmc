#ifndef DFMC_DEMO_DEMOEGL_HPP
#define DFMC_DEMO_DEMOEGL_HPP
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

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <dfmc/eglhelper/NativeWindowManager.hpp>
#include <dfmc/demo/DemoAppConfig.hpp>
#include <dfmc/demo/DemoAppController.hpp>
#include <dfmc/demo/IDemo.hpp>
#include <dfmc/demo/IDemoApp.hpp>
#include <dfmc/demo/IDemoController.hpp>
#include <dfmc/demo/DemoConfig.hpp>
#include <dfmc/base/Pointers.hpp>
#include <dfmc/base/Noncopyable.hpp>

namespace dfmc
{

  class DemoEGL
    : public IDemo
    , private Noncopyable
  {
    DemoAppConfig mConfig;

    EGLDisplay mhEglDisplay;
    EGLContext mhEGLContext;
    EGLSurface mhEglSurface;

    eglhelper::NativeWindowManager mNativeWindowManager;
    std::auto_ptr<eglhelper::INativeWindow> mNativeWin;
    std::auto_ptr<DemoAppController> mAppController;
  public:
    DemoEGL(const DemoConfig& demoConfig, IDemoController& demoController);
    virtual ~DemoEGL();

    virtual int RunDemo();
  private:
    void Cleanup();
  };

}
#endif
