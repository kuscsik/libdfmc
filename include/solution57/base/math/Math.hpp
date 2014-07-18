#ifndef DFMC_BASE_MATH_MATH_HPP
#define DFMC_BASE_MATH_MATH_HPP
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

#include <math.h>

namespace dfmc
{

  class Math
  {
  public:
    static const float PI;  
    static const float TO_RADS;
    static const float TO_DEGREES;

    static float ToDegrees(const float radians) { return radians * TO_DEGREES; }
    static float ToRadians(const float degrees) { return degrees * TO_RADS; }

    static float Tan(float radians) { return (float)tan(radians); }
    static float Sin(float radians) { return (float)sin(radians); }
    static float Cos(float radians) { return (float)cos(radians); }

    static float Sqrt(float value)  { return (float)sqrt(value); }
    
    //! Find the nearest power of two value that is >= the input value
    //! @param value must be >= 0;
    static int ToPowerOfTwo(const int value);
  };
}
#endif
