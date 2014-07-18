#ifndef DFMC_NONCOPYABLE_HPP
#define DFMC_NONCOPYABLE_HPP
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
// Based on boost::noncopyable

// Must be the first include!!
#include <dfmc/base/Config.hpp>


namespace dfmc
{
  class Noncopyable
  {
   protected:
      Noncopyable() {}
      ~Noncopyable() {}
    private:  // emphasize the following members are private
      Noncopyable( const Noncopyable& );
      Noncopyable& operator=( const Noncopyable& );
  };
}

#endif
