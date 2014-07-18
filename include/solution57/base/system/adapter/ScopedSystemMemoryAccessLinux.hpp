#ifdef __linux__
#ifndef DFMC_BASE_SYSTEM_ADAPTER_SCOPEDSYSTEMEMEMORYACCESSLINUX_HPP
#define DFMC_BASE_SYSTEM_ADAPTER_SCOPEDSYSTEMEMEMORYACCESSLINUX_HPP
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
  class ScopedSystemMemoryAccessLinux : private Noncopyable
  {
    int mFd;
    void* mpMem;
    void* mpVirtAddress;
    int mLastValue;
  public:
    ScopedSystemMemoryAccessLinux(const size_t targetAddress);
    ~ScopedSystemMemoryAccessLinux();

    uint8_t GetUint8() const;
    uint16_t GetUint16() const;
    uint32_t GetUint32() const;

    void SetUint8(const uint8_t value);
    void SetUint16(const uint16_t value);
    void SetUint32(const uint32_t value);
  };

}

#endif
#endif
