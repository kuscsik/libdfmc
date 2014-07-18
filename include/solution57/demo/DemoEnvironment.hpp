#ifndef DFMC_DEMO_DEMOENVIRONMENT_HPP
#define DFMC_DEMO_DEMOENVIRONMENT_HPP
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
#include <dfmc/base/math/Point2.hpp>
#include <dfmc/demo/DemoDataProvider.hpp>
#include <dfmc/demo/ICustomDemoEnvironment.hpp>
#include <dfmc/demo/IDemoAppControl.hpp>

namespace dfmc
{
  struct DemoEnvironment
  {
    DFMC::shared_ptr<DemoDataProvider> DataProvider;

    // The screen resolution (at launch)
    Point2 ScreenResolution;

    // Provides access to custom demo environment if any is available
    DFMC::weak_ptr<ICustomDemoEnvironment> CustomEnvironment;

    // Provide access to the demo app control interface
    DFMC::weak_ptr<IDemoAppControl> DemoAppControl;

    DemoEnvironment(const DFMC::shared_ptr<DemoDataProvider>& dataProvider)
      : DataProvider(dataProvider) 
      , ScreenResolution()
      , CustomEnvironment()
    {
    }

    explicit DemoEnvironment(const DFMC::shared_ptr<DemoDataProvider>& dataProvider, const Point2& screenResolution)
      : DataProvider(dataProvider)
      , ScreenResolution(screenResolution)
      , CustomEnvironment()
    {
    }

    explicit DemoEnvironment(const DFMC::shared_ptr<DemoDataProvider>& dataProvider, const Point2& screenResolution, const DFMC::weak_ptr<ICustomDemoEnvironment>& customEnvironment)
      : DataProvider(dataProvider)
      , ScreenResolution(screenResolution)
      , CustomEnvironment(customEnvironment)
    {
    }
  };
}
#endif
