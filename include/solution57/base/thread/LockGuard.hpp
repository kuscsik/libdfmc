#ifndef DFMC_BASE_THREAD_LOCKGUARD_HPP
#define DFMC_BASE_THREAD_LOCKGUARD_HPP
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

#include "dfmc/base/Noncopyable.hpp"
#include "dfmc/base/thread/Mutex.hpp"

#ifdef DFMC_COMPILER_CPP11_THREADS
# define DFMC_LOCK_GUARD_BASE_TYPE std::lock_guard
#else
# pragma message ( "WARNING: LockGuard not implemented for the chosen platform!!" )
  namespace dfmc
  {
    template<typename T> class LockGuardImplemented
    {
    public:
      LockGuardImplemented(T&) {}
    };
  }
# define DFMC_LOCK_GUARD_BASE_TYPE LockGuardImplemented
#endif

namespace dfmc
{

  // Acquires ownership of the given mutex rMutex.
  // - Requires that the current thread owns rMutex.
  // The behavior is undefined if rMutex is destroyed before the lock_guard object is.
  template<typename T> class LockGuard 
    : private DFMC_LOCK_GUARD_BASE_TYPE<T>
    , private Noncopyable
  {
  public:
    LockGuard(T& rMutex) 
      : DFMC_LOCK_GUARD_BASE_TYPE<T>(rMutex) 
    {
    }
  };

}

#endif
