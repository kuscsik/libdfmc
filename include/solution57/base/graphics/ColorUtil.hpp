#ifndef DFMC_BASE_GRAPHICS_COLORUTIL_HPP
#define DFMC_BASE_GRAPHICS_COLORUTIL_HPP
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
#include <dfmc/base/math/Vector4.hpp>

namespace dfmc
{
  class ColorUtil : private Noncopyable
  {
  public:
    static const float ToFloat(const uint8_t value);

    //@brief Convert a ARGB color to a vector 4.
    //       The vector4 encodes colors like this:
    //       X = red, Y = green, Z = blue, W = alpha
    //       ARGB is encoded in the uint32 as this 0xAARRGGBB
    static const Vector4 ARGBToVector4(const uint32_t value);
  };
}

#endif
