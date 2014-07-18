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

#include <dfmc/base/graphics/ColorUtil.hpp>
#include <algorithm>

namespace dfmc
{
  const float ColorUtil::ToFloat(const uint8_t value)
  {
    if (value == 0)
      return 0.0f;
    else if (value == 255)
      return 1.0f;
    return std::max(std::min(value / 255.0f, 1.0f), 0.0f);
  }


  const Vector4 ColorUtil::ARGBToVector4(const uint32_t value)
  {
    // ARGB
    return Vector4(ToFloat((value >> 16) & 0xFF), ToFloat((value >> 8) & 0xFF), ToFloat(value & 0xFF), ToFloat((value >> 24) & 0xFF));
  }

}
