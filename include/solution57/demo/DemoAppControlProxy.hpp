#ifndef DFMC_DEMO_DEMOAPPCONTROLPROXY_HPP
#define DFMC_DEMO_DEMOAPPCONTROLPROXY_HPP
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
#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/demo/IDemoAppControl.hpp>

namespace dfmc
{
  class DemoAppControlProxy 
    : public IDemoAppControl
    , private Noncopyable
  {
    IDemoAppControl& mImpl;
  public:
    DemoAppControlProxy(IDemoAppControl& impl)
      : mImpl(impl)
    {
    }

    virtual void RequestUpdateReset() { mImpl.RequestUpdateReset(); }
    virtual void RequestExit() { mImpl.RequestExit(); }
    virtual void RequestExit(const int exitCode)  { mImpl.RequestExit(exitCode);  }
    virtual void ChangeExitCode(const int exitCode) { mImpl.ChangeExitCode(exitCode); }
  };

}
#endif
