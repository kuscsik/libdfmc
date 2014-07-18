#ifndef DFMC_DEMO_ADEMOAPP_HPP
#define DFMC_DEMO_ADEMOAPP_HPP
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

#include <dfmc/demo/IDemoApp.hpp>
#include <dfmc/demo/DemoEnvironment.hpp>

namespace dfmc
{

  class ADemoApp : public IDemoApp
  {
    DFMC::weak_ptr<IDemoAppControl> mDemoAppControl;
  public:
    ADemoApp(const DemoEnvironment& demoEnvironment);

    virtual DemoState::Enum OnFlipCompleted() 
    {
      return DemoState::Running;
    }
  protected:
    DFMC::shared_ptr<IDemoAppControl> GetDemoAppControl();
  };

}
#endif
