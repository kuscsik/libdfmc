#ifndef DFMC_DEMO_DEMOCONFIG_HPP
#define DFMC_DEMO_DEMOCONFIG_HPP
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
#include <dfmc/base/graphics/RenderConfig.hpp>
#include <dfmc/demo/IDemoAppFactory.hpp>
#include <dfmc/demo/DemoDataProvider.hpp>

namespace dfmc
{
  class DemoConfig
  {
    int mDefaultExitCode;
    RenderConfig mRenderConfig;
    DFMC::shared_ptr<IDemoAppFactory> mAppFactory;
    DFMC::shared_ptr<IDemoAppParams> mDemoAppParams;
    DFMC::shared_ptr<DemoDataProvider> mDemoDataProvider;

  public:
    DemoConfig(const int defaultExitCode, const RenderConfig& renderConfig, const DFMC::shared_ptr<IDemoAppFactory>& appFactory, const DFMC::shared_ptr<IDemoAppParams>& demoAppParams, const DFMC::shared_ptr<DemoDataProvider>& demoDataProvider);

    int GetDefaultExitCode() const;
    const RenderConfig GetRenderConfig() const;
    const DFMC::shared_ptr<IDemoAppFactory> GetAppFactory() const;
    const DFMC::shared_ptr<IDemoAppParams> GetDemoAppParams() const;
    const DFMC::shared_ptr<DemoDataProvider> GetDemoDataProvider() const;

  };
}
#endif
