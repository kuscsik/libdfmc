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

#include <dfmc/base/getopt/OptionUtil.hpp>

namespace dfmc
{

  int OptionUtil::Add(std::deque<Option>& rArgs, const GetoptOptionC* pOptions)
  {
    int count = 0;
    GetoptOptionC current = *pOptions;
    while( current.Opt.name != nullptr )
    {
      Option converted(current.Opt.name, current.Opt.has_arg, current.Opt.flag, current.Opt.val, current.pszDescription);
      rArgs.push_back(converted);
      ++pOptions;
      ++count;
      current = *pOptions;
    }
    return count;
  }

}
