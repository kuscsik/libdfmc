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

#include <dfmc/base/log/LogLocation.hpp>
#include <cassert>

namespace dfmc
{

  LogLocation::LogLocation(const char*const pszFile, const char*const pszFunction, const int line)
    : pszFile(pszFile)
    , pszFunction(pszFunction)
    , line(line)
  {
  }

}
