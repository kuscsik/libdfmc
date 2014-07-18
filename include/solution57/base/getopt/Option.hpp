#ifndef DFMC_BASE_GETOPT_OPTION_HPP
#define DFMC_BASE_GETOPT_OPTION_HPP
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

#include <getopt.h>

namespace dfmc
{
  // @brief Just all simple initialization of 'option'
  struct Option : option
  {
    const char* pszDescription;
    bool isHiddenOption;

#if	__STDC__
    Option(const char* name, const int has_arg, int* flag, const int val, const char*const pszDescription)
#else
    Option(char* name, const int has_arg, int* flag, const int val, const char*const pszDescription)
#endif
    {
      this->name = name;
      this->has_arg = has_arg;
      this->flag = flag;
      this->val = val;
      this->pszDescription = pszDescription;
      this->isHiddenOption = false;
    }

#if	__STDC__
    Option(const char* name, const int has_arg, int* flag, const int val, const char*const pszDescription, const bool isHiddenOption)
#else
    Option(char* name, const int has_arg, int* flag, const int val, const char*const pszDescription, const bool isHiddenOption)
#endif
    {
      this->name = name;
      this->has_arg = has_arg;
      this->flag = flag;
      this->val = val;
      this->pszDescription = pszDescription;
      this->isHiddenOption = isHiddenOption;
    }
  };

}
#endif
