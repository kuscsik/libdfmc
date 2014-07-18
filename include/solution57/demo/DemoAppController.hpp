#ifndef DFMC_DEMO_DEMOAPPCONTROLLER_HPP
#define DFMC_DEMO_DEMOAPPCONTROLLER_HPP
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

#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Pointers.hpp>
#include <dfmc/base/math/Point2.hpp>
#include <dfmc/base/system/HighResolutionTimer.hpp>
#include <dfmc/demo/IDemoApp.hpp>
#include <dfmc/demo/IDemoAppControl.hpp>
#include <dfmc/demo/IDemoAppParams.hpp>
#include <dfmc/demo/IDemoController.hpp>
#include <dfmc/demo/DemoAppControlProxy.hpp>
#include <dfmc/demo/DemoConfig.hpp>
#include <dfmc/demo/DemoEnvironment.hpp>
#include <dfmc/demo/DemoState.hpp>


namespace dfmc
{
  // Takes care of driving the app at fixed time steps
  class DemoAppController : public IDemoAppControl
  {
    DemoConfig mDemoConfig;
    std::auto_ptr<IDemoApp> mDemoApp;
    IDemoController& mDemoController;
    bool mRestartOnResize;
    HighResolutionTimer mTimer;
    DemoEnvironment mDemoEnvironment;
    bool mIsFirstRender;
    uint64_t mTimeThen;
    uint64_t mAccumulatedTime;
    uint64_t mExpectedFrameTime;
    uint64_t mMaxFrameTime;
    DemoState::Enum mDemoState;
    bool mHasUpdateResetRequest;
    int mDefaultExitCode;
    mutable bool mHasExitRequest;
    mutable int mExitCode;

    DFMC::shared_ptr<DemoAppControlProxy> mProxy;
  public:
    // @brief allocate the controller and app
    DemoAppController(const DemoConfig& demoConfig, IDemoController& demoController, const DemoEnvironment& demoEnvironment, const bool hasScreenResolution, const bool restartOnResize);
    virtual ~DemoAppController();

    bool HasExitRequest() const;

    void Render(const Point2& screenResolution);
    void SequenceCompleted();

    int CloseApp();

    DemoState::Enum GetDemoState() const;

    virtual void RequestUpdateReset();
    virtual void RequestExit();
    virtual void RequestExit(const int exitCode);
    virtual void ChangeExitCode(const int exitCode);
  private:

    void DoRequestExit() const;
    void DoRequestExit(const int exitCode) const;

    void ResetTimer();
  };

}
#endif
