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

#include <dfmc/demo/DemoAppController.hpp>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/log/Log.hpp>
#include <dfmc/base/system/HighResolutionTimer.hpp>
#include <dfmc/base/thread/Thread.hpp>
#include <cassert>
#include <deque>
#include <iostream>
#include <vector>

// Sleep 'one' frame
#define FREEZE_SLEEP_TIME 16

namespace dfmc
{
  // Since we know that it make take a very long time to render frames and
  // that its not because of 'FixedUpdate' calls we more or less disable
  // maxFrameTime checks that is used to catchup

  DemoAppController::DemoAppController(const DemoConfig& demoConfig, IDemoController& demoController, const DemoEnvironment& demoEnvironment, const bool hasScreenResolution, const bool restartOnResize)
    : mDemoConfig(demoConfig)
    , mDemoApp()
    , mDemoController(demoController)
    , mRestartOnResize(restartOnResize)
    , mTimer()
    , mDemoEnvironment(demoEnvironment)
    , mIsFirstRender(true)
    , mTimeThen(0)
    , mAccumulatedTime(0)
    , mExpectedFrameTime(1000 / 60)     // 
    , mMaxFrameTime(0xFFFFFFFF) // 1000 / 2; // FIX: supply this at construction
    , mDemoState(DemoState::Running)
    , mHasUpdateResetRequest(false)
    , mDefaultExitCode(demoConfig.GetDefaultExitCode())
    , mHasExitRequest(false)
    , mExitCode(0)
    , mProxy()
  {
    mProxy.reset(new DemoAppControlProxy(*this));

    if (hasScreenResolution)
    {
      mDemoEnvironment.DemoAppControl = mProxy;
      mDemoApp.reset(demoConfig.GetAppFactory()->Allocate(mDemoEnvironment, demoConfig.GetDemoAppParams()));
      assert(mDemoApp.get() != nullptr);
    }
  }


  DemoAppController::~DemoAppController()
  {
    // We reset the proxy here to ensure its one of the first things that gets destroyed during destruction.
    mProxy.reset();
  }


  bool DemoAppController::HasExitRequest() const
  {
    bool hasExitRequest = mDemoController.HasExitRequest();
    if (mDemoApp.get() != nullptr)
    {
      bool hasDemoExitRequest = mHasExitRequest;
      if (hasExitRequest && !hasDemoExitRequest)
        DoRequestExit();

      hasExitRequest |= hasDemoExitRequest;
    }
    return hasExitRequest;
  }


  void DemoAppController::Render(const Point2& screenResolution)
  {
    if (mDemoState == DemoState::Running)
    {
      if (mDemoApp.get() != nullptr && mRestartOnResize && screenResolution != mDemoEnvironment.ScreenResolution)
      {
        // Release the app
        mDemoApp.reset();
      }

      // Handle delayed app initialization
      if (mDemoApp.get() == nullptr)
      {
        DemoEnvironment demoEnvironment(mDemoConfig.GetDemoDataProvider(), screenResolution);
        demoEnvironment.DemoAppControl = mProxy;
        mDemoApp.reset(mDemoConfig.GetAppFactory()->Allocate(demoEnvironment, mDemoConfig.GetDemoAppParams()));
        assert(mDemoApp.get() != nullptr);

        // Reset all time stuff
        ResetTimer();
        // Just accept the new resolution
        mDemoEnvironment.ScreenResolution = screenResolution;
      }

      // Detect resolution changes
      if (screenResolution != mDemoEnvironment.ScreenResolution)
      {
        mDemoEnvironment.ScreenResolution = screenResolution;
        mDemoApp->Resize(mDemoEnvironment.ScreenResolution.X, mDemoEnvironment.ScreenResolution.Y);
      }

      if (mHasUpdateResetRequest)
      {
        mHasUpdateResetRequest = false;
        mIsFirstRender = true;
      }

      // We reset the timer upon the first render request
      if (mIsFirstRender)
      {
        ResetTimer();
        mIsFirstRender = false;
      }

      assert(mDemoApp.get() != nullptr);
      // Allow constructors to exit
      if (HasExitRequest())
        return;

      // Event loop
      {
        // Standard fixed timestep algorithm 
        // If the display refresh rate was known we could 
        // create a much better implementation of it
        const uint64_t timeNow = mTimer.GetTime();
        //DFMCLOG_LINE("Now: " << timeNow);

        assert(timeNow >= mTimeThen);

        uint64_t timeDiff = timeNow - mTimeThen;
        mTimeThen = timeNow;
        if (timeDiff >= mMaxFrameTime)
          timeDiff = mExpectedFrameTime;

        mAccumulatedTime += timeDiff;
        //      if (mAccumulatedTime >= mExpectedFrameTime)
        //        std::cout << "draw: " << mAccumulatedTime << std::endl;
        //      else
        //        std::cout << "WARNING: drawing-same-frame: " << mAccumulatedTime << std::endl;

        int updateCount = 0;
        while (mAccumulatedTime >= mExpectedFrameTime)
        {
          mDemoApp->FixedUpdate();
          mAccumulatedTime -= mExpectedFrameTime;
          ++updateCount;
        }

        mDemoApp->Update(float((updateCount * mExpectedFrameTime) / 1000.0f));
        mDemoApp->Draw();
      }
    }
  }


  void DemoAppController::SequenceCompleted()
  {
    if (mDemoState == DemoState::Running && mDemoApp.get() != nullptr)
    {
      mDemoState = mDemoApp->OnFlipCompleted();
    }
    else if (mDemoState == DemoState::Freeze)
    {
      Thread::Sleep(FREEZE_SLEEP_TIME);
    }
  }


  int DemoAppController::CloseApp()
  {
    // Ensure that the app has been marked as requesting a exit
    if (mDemoApp.get() != nullptr && !mHasExitRequest)
      DoRequestExit();

    // Free the app
    mDemoApp.reset();
    return mExitCode;
  }


  DemoState::Enum DemoAppController::GetDemoState() const
  {
    return mDemoState;
  }


  void DemoAppController::RequestUpdateReset()
  {
    mHasUpdateResetRequest = true;
  }




  void DemoAppController::RequestExit()
  {
    DoRequestExit();
  }


  void DemoAppController::RequestExit(const int exitCode)
  {
    DoRequestExit(exitCode);
  }


  void DemoAppController::ChangeExitCode(const int exitCode)
  {
    if (mHasExitRequest && mExitCode == mDefaultExitCode)
      mExitCode = exitCode;
    else
    {
      DFMCLOG_LINE_IF(!mHasExitRequest, "WARNING: No exit request exists. Request ignored.");
      DFMCLOG_LINE_IF(mHasExitRequest, "WARNING: No exit code is already set. Request ignored.");
    }
  }


  void DemoAppController::DoRequestExit() const
  {
    DoRequestExit(mDefaultExitCode);
  }


  void DemoAppController::DoRequestExit(const int exitCode) const
  {
    if (!mHasExitRequest)
    {
      mHasExitRequest = true;
      mExitCode = exitCode;
    }
    else
    {
      DFMCLOG_LINE("WARNING: exit has already been requested with status code: " << (int)mExitCode << ". Request ignored.");
    }
  }


  void DemoAppController::ResetTimer()
  {
    mTimeThen = mTimer.GetTime() - mExpectedFrameTime;
    mAccumulatedTime = 0;
  }


}
