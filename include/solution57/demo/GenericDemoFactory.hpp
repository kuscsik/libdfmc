#ifndef DFMC_DEMO_GENERICDEMOFACTORY_HPP
#define DFMC_DEMO_GENERICDEMOFACTORY_HPP
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

#include <dfmc/demo/IDemoFactory.hpp>

namespace dfmc
{
  template<typename T>
  class GenericDemoFactory : public IDemoFactory
  {
  public:
    virtual IDemo* Allocate(const DemoConfig& demoConfig, IDemoController& demoController)
    {
      return new T(demoConfig, demoController);
    }
  };
}
#endif
