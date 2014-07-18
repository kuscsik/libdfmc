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

#ifdef _WIN32
# include <Windows.h>
#elif defined(__linux__)
# include <time.h>
#else
# error Unsupported platform
#endif

#include <dfmc/base/system/HighResolutionTimer.hpp>

namespace dfmc 
{
  HighResolutionTimer::HighResolutionTimer()
  {
#ifdef _WIN32
    {
      LARGE_INTEGER value;
      QueryPerformanceFrequency(&value);
      mFrequency = value.QuadPart / 1000L;
    }
#endif
  }


  uint64_t HighResolutionTimer::GetTime() const
  {
#ifdef _WIN32
    {
      LARGE_INTEGER value;
      QueryPerformanceCounter(&value);
      return (value.QuadPart / mFrequency);
    }
#elif defined(__linux__)
    {
      struct timespec currentTime;
      clock_gettime(CLOCK_MONOTONIC, &currentTime);
      uint64_t time = currentTime.tv_sec;
      time *= 1000;
      time += (currentTime.tv_nsec / 1000000);
      return time;
    }
#endif
  }
}
