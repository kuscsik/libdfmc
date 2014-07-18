#ifndef DFMC_BASE_GETOPT_IOPTIONPARSER_HPP
#define DFMC_BASE_GETOPT_IOPTIONPARSER_HPP
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
#include <dfmc/base/Pointers.hpp>
#include <dfmc/base/getopt/Option.hpp>
#include <dfmc/cbase/getopt/OptionParseResult.h>
#include <deque>
#include <string>

namespace dfmc
{
  class IOptionParser
  {
  public:
    virtual ~IOptionParser() {}

    // @brief Get a list of arguments
    // @param rArgs a list of args in the getopt options format + a description used for display help.
    // @param rOptions getopt's optstring.
    virtual void ExtractArguments(std::deque<Option>& rArgs, std::string& rOptions) = 0;

    // @brief Parse the given argument
    // @param val = the val you configured for the argument
    // @param pszOptArg = the argument if any.
    virtual OptionParseResult::Enum Parse(const int val, const char*const pszOptArg, const int optionIndex) = 0;

    // @brief Called when the parsing completed successfully
    // @return true to continue running, false to stop the program
    virtual bool ParsingCompleted(const bool bDevOverride) = 0;
  };

}
#endif
