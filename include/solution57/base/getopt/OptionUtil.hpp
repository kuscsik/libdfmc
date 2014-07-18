#ifndef DFMC_BASE_GETOPT_OPTIONUTIL_HPP
#define DFMC_BASE_GETOPT_OPTIONUTIL_HPP
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

#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/base/getopt/Option.hpp>
#include <dfmc/cbase/getopt/GetoptOptionC.h>
#include <deque>

namespace dfmc
{
  class OptionUtil : private dfmc::Noncopyable
  {
  public:
    // @brief Add the 'C' encoded options to rArgs
    // @return the number of arguments that was added
    static int Add(std::deque<Option>& rArgs, const GetoptOptionC* pOptions);
  };

}
#endif
