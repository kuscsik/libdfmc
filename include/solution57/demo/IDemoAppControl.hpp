#ifndef DFMC_DEMO_IDEMOAPPCONTROL_HPP
#define DFMC_DEMO_IDEMOAPPCONTROL_HPP
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


namespace dfmc
{
  // Takes care of driving the app at fixed time steps
  class IDemoAppControl
  {
  public:
    virtual ~IDemoAppControl() {}

    virtual void RequestUpdateReset() = 0;
    virtual void RequestExit() = 0;
    virtual void RequestExit(const int exitCode) = 0;

    //! @brief Changes the exit code.
    //!        Will ignore the change request if not in 'requested exit' mode and log a warning.
    //!        Will ignore the change request if the current exit code isnt defaultExitCode and log a warning
    virtual void ChangeExitCode(const int exitCode) = 0;
  };

}
#endif
