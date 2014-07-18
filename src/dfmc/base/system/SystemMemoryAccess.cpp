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

#include <dfmc/base/system/SystemMemoryAccess.hpp>
#include <dfmc/base/system/ScopedSystemMemoryAccess.hpp>
#include <iostream>
#include <stdio.h>

namespace dfmc 
{
  uint8_t SystemMemoryAccess::GetUint8(const size_t targetAddress)
  {
    ScopedSystemMemoryAccess mem(targetAddress);
    return mem.GetUint8();
  }


  uint16_t SystemMemoryAccess::GetUint16(const size_t targetAddress)
  {
    ScopedSystemMemoryAccess mem(targetAddress);
    return mem.GetUint16();
  }


  uint32_t SystemMemoryAccess::GetUint32(const size_t targetAddress)
  {
    ScopedSystemMemoryAccess mem(targetAddress);
    return mem.GetUint32();
  }


  void SystemMemoryAccess::SetUint8(const size_t targetAddress, const uint8_t value, const uint8_t mask)
  {
    ScopedSystemMemoryAccess mem(targetAddress);
    uint8_t oldValue = mem.GetUint8();
    return mem.SetUint8((oldValue & ~mask)|(value & mask));
  }


  void SystemMemoryAccess::SetUint16(const size_t targetAddress, const uint16_t value, const uint16_t mask)
  {
    ScopedSystemMemoryAccess mem(targetAddress);
    uint16_t oldValue = mem.GetUint16();
    return mem.SetUint16((oldValue & ~mask)|(value & mask));
  }


  void SystemMemoryAccess::SetUint32(const size_t targetAddress, const uint32_t value, const uint32_t mask)
  {
    ScopedSystemMemoryAccess mem(targetAddress);
    uint32_t oldValue = mem.GetUint32();
    return mem.SetUint32((oldValue & ~mask)|(value & mask));
  }

}
