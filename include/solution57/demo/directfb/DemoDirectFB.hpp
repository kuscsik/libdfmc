#ifdef DFMC_HAS_DIRECTFB
#ifndef DFMC_DEMO_DEMODIRECTFB_HPP
#define DFMC_DEMO_DEMODIRECTFB_HPP
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

#include <dfmc/base/Pointers.hpp>
#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/base/math/Rectangle.hpp>
#include <dfmc/demo/DemoAppConfig.hpp>
#include <dfmc/demo/DemoAppController.hpp>
#include <dfmc/demo/IDemo.hpp>
#include <dfmc/demo/IDemoApp.hpp>
#include <dfmc/demo/IDemoController.hpp>
#include <dfmc/demo/DemoConfig.hpp>
#include <dfmc/demo/directfb/CustomDemoEnvironmentDirectFB.hpp>
#include <directfb.h>

namespace dfmc
{

  class DemoDirectFB
    : public IDemo
    , private Noncopyable
  {
    DemoAppConfig mConfig;
    Rectangle mScreenArea;

    IDirectFB* mpDfb;
    IDirectFBSurface* mpDfbsurface;
    IDirectFBDisplayLayer* mpDfblayer;
    IDirectFBWindow* mpDfbwindow;

    DFMC::shared_ptr<CustomDemoEnvironmentDirectFB> mCustomDemoEnv;
    std::auto_ptr<DemoAppController> mAppController;

    bool mDirectMode;
  public:
    DemoDirectFB(const DemoConfig& demoConfig, IDemoController& demoController);
    virtual ~DemoDirectFB();

    virtual int RunDemo();
  private:
    void Cleanup();
  };

}
#endif
#endif
