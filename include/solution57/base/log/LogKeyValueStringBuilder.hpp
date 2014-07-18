#ifndef DFMC_BASE_LOG_LOGKEYVALUESTRINGBUILDER_HPP
#define DFMC_BASE_LOG_LOGKEYVALUESTRINGBUILDER_HPP
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
#include <dfmc/base/Pointers.hpp>
#include <sstream>

namespace dfmc
{
  class LogStringEncoder;

  class LogKeyValueStringBuilder : private dfmc::Noncopyable
  {
    std::stringstream mStream;
    int mEntries;
    std::auto_ptr<LogStringEncoder> mEncoder;
  public:
    LogKeyValueStringBuilder();
    ~LogKeyValueStringBuilder();

    void Clear();
    void Add(const char*const pszKey, const bool value);
    void Add(const char*const pszKey, const uint8_t value);
    void Add(const char*const pszKey, const int8_t value);
    void Add(const char*const pszKey, const uint16_t value);
    void Add(const char*const pszKey, const int16_t value);
    void Add(const char*const pszKey, const uint32_t value);
    void Add(const char*const pszKey, const int32_t value);
    void Add(const char*const pszKey, const uint64_t value);
    void Add(const char*const pszKey, const int64_t value);
    void Add(const char*const pszKey, const float value);
    void Add(const char*const pszKey, const double value);

    void Add(const char*const pszKey, const char*const pszValue);
    void Add(const char*const pszKey, const std::string& value);

    // @brief Extract the content as a string
    const std::string GetString() const;
  };

}

#endif
