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

#include <dfmc/demo/DemoConfig.hpp>
#include <cassert>

namespace dfmc
{
  DemoConfig::DemoConfig(const int defaultExitCode, const RenderConfig& renderConfig, const DFMC::shared_ptr<IDemoAppFactory>& appFactory, const DFMC::shared_ptr<IDemoAppParams>& demoAppParams, const DFMC::shared_ptr<DemoDataProvider>& demoDataProvider)
    : mDefaultExitCode(defaultExitCode)
    , mRenderConfig(renderConfig)
    , mAppFactory(appFactory)
    , mDemoAppParams(demoAppParams)
    , mDemoDataProvider(demoDataProvider)
  {
    assert(mAppFactory);
    assert(mDemoAppParams);
    assert(mDemoDataProvider);
  }


  int DemoConfig::GetDefaultExitCode() const
  {
    return mDefaultExitCode;
  }


  const RenderConfig DemoConfig::GetRenderConfig() const
  {
    return mRenderConfig;
  }


  const DFMC::shared_ptr<IDemoAppFactory> DemoConfig::GetAppFactory() const
  {
    return mAppFactory;
  }


  const DFMC::shared_ptr<IDemoAppParams> DemoConfig::GetDemoAppParams() const
  {
    return mDemoAppParams;
  }


  const DFMC::shared_ptr<DemoDataProvider> DemoConfig::GetDemoDataProvider() const
  {
    return mDemoDataProvider;
  }

}
