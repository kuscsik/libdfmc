#ifdef __linux__
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

#include <dfmc/base/system/adapter/ScopedSystemMemoryAccessLinux.hpp>
#include <dfmc/base/Exceptions.hpp>
#include <dfmc/base/log/Log.hpp>

#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h> // mmap, munmap
#include <sys/types.h>
#include <sys/stat.h>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

namespace dfmc 
{
  ScopedSystemMemoryAccessLinux::ScopedSystemMemoryAccessLinux(const size_t targetAddress)
    : mFd(0)
    , mpMem(nullptr)
    , mpVirtAddress(nullptr)
    , mLastValue(0)
  {
    if ((mFd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
      const std::string strError(strerror(errno));
      throw IOException(strError);
    }

    // Map one page
    mpMem = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mFd, targetAddress & ~MAP_MASK);
    if (mpMem == (void *)-1)
    {
      const std::string strError(strerror(errno));
      throw IOException(strError);
    }

    mpVirtAddress = ((uint8_t*)mpMem) + (targetAddress & MAP_MASK);
  }


  ScopedSystemMemoryAccessLinux::~ScopedSystemMemoryAccessLinux()
  {
    if (munmap(mpMem, MAP_SIZE) == -1)
    {
      DFMCLOG_LINE("WARNING: SystemMemoryAccess munmap failed with '" << strerror(errno) << "'");
    }
    close(mFd);
  }

  uint8_t ScopedSystemMemoryAccessLinux::GetUint8() const
  {
    return *((uint8_t *)mpVirtAddress);
  }

  uint16_t ScopedSystemMemoryAccessLinux::GetUint16() const
  {
    return *((uint16_t *)mpVirtAddress);
  }

  uint32_t ScopedSystemMemoryAccessLinux::GetUint32() const
  {
    return *((uint32_t *)mpVirtAddress);
  }

  void ScopedSystemMemoryAccessLinux::SetUint8(const uint8_t value)
  {
    *((uint8_t *)mpVirtAddress) = value;
    mLastValue = *((uint8_t *)mpVirtAddress);
  }

  void ScopedSystemMemoryAccessLinux::SetUint16(const uint16_t value)
  {
    *((uint16_t *)mpVirtAddress) = value;
    mLastValue = *((uint16_t *)mpVirtAddress);
  }

  void ScopedSystemMemoryAccessLinux::SetUint32(const uint32_t value)
  {
    *((uint32_t *)mpVirtAddress) = value;
    mLastValue = *((uint32_t *)mpVirtAddress);
  }

}
#endif