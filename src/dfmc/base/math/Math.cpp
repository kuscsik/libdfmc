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

#include <dfmc/base/math/Math.hpp>
#include <cassert>
#include <algorithm>

namespace dfmc
{

  const float Math::PI = 3.14159265f;  
  const float Math::TO_RADS = (Math::PI / 180.0f);
  const float Math::TO_DEGREES = (1.0f / (Math::PI / 180.0f));


  int Math::ToPowerOfTwo(const int value)
  {
    assert( value >= 0 );
    if (value > 0)
    {
      int tmpValue = value;
      --tmpValue;
      tmpValue |= (tmpValue >> 1);
      tmpValue |= (tmpValue >> 2);
      tmpValue |= (tmpValue >> 4);
      tmpValue |= (tmpValue >> 8);
      tmpValue |= (tmpValue >> 16);
      ++tmpValue; // Val is now the next highest power of 2.
      return tmpValue;
    }
    return 1;
  }


}
