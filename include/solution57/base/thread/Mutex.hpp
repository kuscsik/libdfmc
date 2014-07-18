#ifndef DFMC_BASE_THREAD_MUTEX_HPP
#define DFMC_BASE_THREAD_MUTEX_HPP
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


#ifdef DFMC_COMPILER_CPP11_THREADS
# include <mutex>
# define DFMC_MUTEX_BASE_TYPE std::mutex
#else
# pragma message ( "WARNING: Mutex not implemented for the chosen platform!!" )
# include <dfmc/base/Noncopyable.hpp>
  namespace dfmc { class MutexNotImplemented : private Noncopyable {}; }
# define DFMC_MUTEX_BASE_TYPE MutexNotImplemented
#endif

namespace dfmc
{
  typedef DFMC_MUTEX_BASE_TYPE Mutex;
}

#endif
