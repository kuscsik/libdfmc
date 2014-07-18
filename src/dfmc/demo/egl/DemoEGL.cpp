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

#include <dfmc/demo/egl/DemoEGL.hpp>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/log/Log.hpp>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

#define EGL_CHECK(X) \
  X; \
  { \
    EGLint eglError = eglGetError(); \
    if (eglError != EGL_SUCCESS) \
    { \
      fprintf(stdout, "ERROR: eglGetError() = %i (0x%.8x) at line %i\n", eglError, eglError, __LINE__); \
      throw dfmc::GraphicsException("EglError on "#X); \
    } \
  }

namespace dfmc
{
  namespace
  {
    void BuildEglAttributes(std::deque<EGLint>& eglAttributes, const bool bUseOpenGLES, const bool bUseOpenVG, const bool bForceConformance)
    {
      eglAttributes.push_back(EGL_RED_SIZE);
      eglAttributes.push_back(8);
      eglAttributes.push_back(EGL_GREEN_SIZE);
      eglAttributes.push_back(8);
      eglAttributes.push_back(EGL_BLUE_SIZE);
      eglAttributes.push_back(8);
      if( bUseOpenGLES )
      {
        eglAttributes.push_back(EGL_DEPTH_SIZE);
        eglAttributes.push_back(16);
        eglAttributes.push_back(EGL_RENDERABLE_TYPE);
        eglAttributes.push_back(EGL_OPENGL_ES2_BIT);
      }
      if( bUseOpenVG )
      {
        eglAttributes.push_back(EGL_ALPHA_SIZE);
        eglAttributes.push_back(8);
        eglAttributes.push_back(EGL_SURFACE_TYPE);
        eglAttributes.push_back(EGL_WINDOW_BIT);
        eglAttributes.push_back(EGL_RENDERABLE_TYPE);
        eglAttributes.push_back(EGL_OPENVG_BIT);
      }
      if( bUseOpenGLES && bForceConformance )
      {
        eglAttributes.push_back(EGL_CONFORMANT);
        eglAttributes.push_back(EGL_OPENGL_ES2_BIT);
      }
      eglAttributes.push_back(EGL_NONE);
    }

    Point2 GetScreenResolution(EGLDisplay hEglDisplay, EGLSurface hEglSurface)
    {
      EGLint windowWidth;
      EGLint windowHeight;
      eglQuerySurface(hEglDisplay, hEglSurface, EGL_WIDTH, &windowWidth);
      eglQuerySurface(hEglDisplay, hEglSurface, EGL_HEIGHT, &windowHeight);
      return Point2(windowWidth, windowHeight);
    }
  }

  DemoEGL::DemoEGL(const DemoConfig& demoConfig, IDemoController& demoController)
    : mConfig(demoConfig.GetAppFactory()->GetConfig())
    , mhEglDisplay(EGL_NO_DISPLAY)
    , mhEGLContext(EGL_NO_CONTEXT)
    , mhEglSurface(EGL_NO_SURFACE)
    , mNativeWindowManager()
    , mNativeWin()
    , mAppController()
  {

    using namespace eglhelper;

    // Configure
    std::deque<EGLint> attributes;
    BuildEglAttributes(attributes, mConfig.UseOpenGLES, mConfig.UseOpenVG, mConfig.ForceConformance);

    std::vector<EGLint> eglAttributes(attributes.begin(), attributes.end());

    EGLint theOpenGLEglContextAttributes[] =
    {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
    };
    EGLint theOpenVGEglContextAttributes[] =
    {
      EGL_NONE
    };
    EGLint* pEglContextAttributes = theOpenGLEglContextAttributes;

    EGLConfig	aEGLConfigs[1];
    EGLint		cEGLConfigs;

    // EGL Init
    EGLNativeDisplayType hDisplay = mNativeWindowManager.GetDisplayType();
    try
    {
      mhEglDisplay = EGL_CHECK(eglGetDisplay(hDisplay));

      EGL_CHECK(eglInitialize(mhEglDisplay, nullptr, nullptr));

      if(mConfig.UseOpenVG == true)
      {
          EGL_CHECK(eglBindAPI(EGL_OPENVG_API));
          pEglContextAttributes = theOpenVGEglContextAttributes;
      }

      EGL_CHECK(eglChooseConfig(mhEglDisplay, &eglAttributes[0], aEGLConfigs, 1, &cEGLConfigs));
      if (cEGLConfigs == 0)
        throw GraphicsException("No EGL configurations were returned.");

      const EGLConfig config = aEGLConfigs[0];

      mNativeWin.reset(mNativeWindowManager.CreateNativeWindow(demoConfig.GetRenderConfig(), mhEglDisplay, config));
      EGLNativeWindowType hWindow = mNativeWin->GetWindowType();

      mhEglSurface = EGL_CHECK(eglCreateWindowSurface(mhEglDisplay, config, hWindow, nullptr));
      if (mhEglSurface == EGL_NO_SURFACE)
        throw GraphicsException("Failed to create EGL surface.");

      mhEGLContext = EGL_CHECK(eglCreateContext(mhEglDisplay, aEGLConfigs[0], EGL_NO_CONTEXT, pEglContextAttributes));
      if (mhEGLContext == EGL_NO_CONTEXT)
        throw GraphicsException("Failed to create EGL context.");

      EGL_CHECK(eglMakeCurrent(mhEglDisplay, mhEglSurface, mhEglSurface, mhEGLContext));
      EGL_CHECK(eglSwapInterval(mhEglDisplay, 1));


      const DemoEnvironment demoEnvironment(demoConfig.GetDemoDataProvider(), GetScreenResolution(mhEglDisplay, mhEglSurface));
      // Everything is setup lets spawn the app and let it play
      mAppController.reset(new DemoAppController(demoConfig, demoController, demoEnvironment, true, mConfig.RestartOnResize));
    }
    catch (const std::exception&)
    {
      Cleanup();
      throw;
    }
  }


  DemoEGL::~DemoEGL()
  {
    Cleanup();
  }


  int DemoEGL::RunDemo()
  {
    const Point2 screenResolution = GetScreenResolution(mhEglDisplay, mhEglSurface);

    // Event loop
    while (mNativeWin->ProcessMessages() && ! mAppController->HasExitRequest())
    {
      if (mAppController->GetDemoState() == DemoState::Running)
      {
        mAppController->Render(screenResolution);

        if (!eglSwapBuffers(mhEglDisplay, mhEglSurface))
        {
          DFMCLOG_LINE("Failed to swap buffers.");
        }
      }
      mAppController->SequenceCompleted();
    }
    return mAppController->CloseApp();
  }


  void DemoEGL::Cleanup()
  {
    // Release the app first, since it expects GL to be ready
    mAppController.reset();

    if (mConfig.UseOpenGLES)
    {
      // Cleanup shaders
      glUseProgram(0);
    }

    // EGL clean up
    eglMakeCurrent(mhEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroySurface(mhEglDisplay, mhEglSurface);
    mhEglSurface = EGL_NO_SURFACE;
    eglDestroyContext(mhEglDisplay, mhEGLContext);
    mhEGLContext = EGL_NO_CONTEXT;
    eglTerminate(mhEglDisplay);
    mhEglDisplay = EGL_NO_DISPLAY;

    // Release the window before the manager that was used to create it
    mNativeWin.reset();
  }

}
