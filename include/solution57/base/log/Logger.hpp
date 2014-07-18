#ifndef DFMC_BASE_LOG_LOGGER_HPP
#define DFMC_BASE_LOG_LOGGER_HPP
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
#include <dfmc/base/log/LogLocation.hpp>
#include <dfmc/base/log/LogKeyValueStringBuilder.hpp>
#include <string>
#include <sstream>

namespace dfmc
{
  class LogStringEncoder;

  // WARNING: It is not a good idea to utilize this code before 'main' has been hit (so don't use it from static object constructors)
  class Logger : dfmc::Noncopyable
  {
  public:
    static void WriteLine(const LogLocation& location, const char*const psz);
    static void WriteLine(const LogLocation& location, const char*const psz, const LogKeyValueStringBuilder& builder);
    static void WriteLine(const LogLocation& location, const std::string& str);
    static void WriteLine(const LogLocation& location, const std::string& str, const LogKeyValueStringBuilder& builder);
    static void WriteLine(const LogLocation& location, const std::stringstream& stream);
    static void WriteLine(const LogLocation& location, const std::stringstream& stream, const LogKeyValueStringBuilder& builder);
    static void WriteLine(const LogLocation& location, const LogKeyValueStringBuilder& builder);
  };

}

#endif
