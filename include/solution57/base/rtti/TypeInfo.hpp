#ifndef DFMC_BASE_RTTI_TYPEINFO_HPP
#define DFMC_BASE_RTTI_TYPEINFO_HPP
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

#include <typeinfo>
#include <cassert>

namespace dfmc
{
  // A safe typeinfo class that can be stored and copared.
  // Based on Modern C++ Design: Generic Programming and Design Patterns Applied
  // In C++11 std::type_index can be used instead
  class TypeInfo
  {
  public:
    // Constructors
    TypeInfo(); // needed for containers
    TypeInfo(const std::type_info&); // non-explicit

    // Access for the wrapped std::type_info
    const std::type_info& Get() const;

    // Compatibility functions
    bool before(const TypeInfo& rhs) const;

    const char* name() const;

  private:
    const std::type_info* mpInfo;
  };

  // Comparison operators
  inline bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
    // type_info::operator== return type is int in some VC libraries
  {
    return (lhs.Get() == rhs.Get()) != 0;
  }

  inline bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return lhs.before(rhs);
  }

  inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return !(lhs == rhs);
  }

  inline bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return rhs < lhs;
  }

  inline bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return !(lhs > rhs);
  }

  inline bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
  {
    return !(lhs < rhs);
  }
}

#endif
