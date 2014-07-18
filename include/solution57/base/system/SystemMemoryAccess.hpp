#ifndef DFMC_BASE_SYSTEM_SYSTEMEMEMORYACCESS_HPP
#define DFMC_BASE_SYSTEM_SYSTEMEMEMORYACCESS_HPP
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
#include <cstddef>

namespace dfmc 
{

  // @brief Direct memory access
  // @note  This is not supported on all platforms!
  class SystemMemoryAccess : private Noncopyable
  {
  public:
    static uint8_t GetUint8(const size_t targetAddress);
    static uint16_t GetUint16(const size_t targetAddress);
    static uint32_t GetUint32(const size_t targetAddress);

    static void SetUint8(const size_t targetAddress, const uint8_t value, const uint8_t mask = 0xFF);
    static void SetUint16(const size_t targetAddress, const uint16_t value, const uint16_t mask = 0xFFFF);
    static void SetUint32(const size_t targetAddress, const uint32_t value, const uint32_t mask = 0xFFFFFFFF);
};

}

#endif
