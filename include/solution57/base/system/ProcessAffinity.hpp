#ifndef DFMC_BASE_SYSTEM_PROCESSAFFINITY_HPP
#define DFMC_BASE_SYSTEM_PROCESSAFFINITY_HPP
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

// Must be the first include!!
#include <dfmc/base/Config.hpp>

#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Noncopyable.hpp>

namespace dfmc 
{

  // @brief Set the process affinty
  class ProcessAffinity : private Noncopyable
  {
  public:
    //! @brief Set the affinity mask
    //! @param cpuId = the id of the cpu to set the affinity to (0 == first available, 1 = second available) 
    //! @note Currently we only support setting the affinity to one CPU
    static void SetAffinity(const int cpuId);
  };

}

#endif
