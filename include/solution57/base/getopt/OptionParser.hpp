#ifndef DFMC_BASE_GETOPT_OPTIONPARSER_HPP
#define DFMC_BASE_GETOPT_OPTIONPARSER_HPP
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
#include <dfmc/base/getopt/IOptionParser.hpp>
#include <vector>

namespace dfmc
{
  class OptionParser : private dfmc::Noncopyable
  {
    bool mIsVerbose;
    bool mbIncludeProcessAffinityOption;
  public:
    OptionParser();
    OptionParser(const bool bIncludeProcessAffinityOption);
    bool Parse(int argc, char **argv, IOptionParser& optionParser);
    bool Parse(int argc, char **argv, const std::vector<IOptionParser*>& optionParsers);

    bool IsVerbose() const;
  };

}
#endif
