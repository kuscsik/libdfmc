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

#include <dfmc/base/thread/Thread.hpp>

#ifdef _WIN32
# include <windows.h>
# define DFMC_SLEEP(mSECS) ::Sleep(mSECS);
#elif defined(__linux__)
# include <time.h>
# define DFMC_SLEEP(mSECS) { struct timespec tIME; tIME.tv_sec = ((mSECS) / 1000); tIME.tv_nsec = ((mSECS) % 1000) * 1000000; nanosleep(&tIME, nullptr); }
#elif defined(DFMC_COMPILER_CPP11_THREADS)
# include <chrono>
# include <thread>
# define DFMC_SLEEP(mSECS) std::this_thread::sleep_for(std::chrono::milliseconds(mSECS));
#endif

namespace dfmc
{
  //! @brief Suspends the current thread for the specified number of milliseconds.
  void Thread::Sleep(const uint32_t msecs)
  {
    DFMC_SLEEP(msecs)
  }
}

