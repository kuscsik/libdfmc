#ifndef DFMC_BASE_MATH_BOX_HPP
#define DFMC_BASE_MATH_BOX_HPP
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

#include <dfmc/base/math/Vector2.hpp>

namespace dfmc
{
  // A box defines a rectangle shaped area between x1 -> x2, y1 -> y2 
  // The following is valid
  //  x1 <= x2 || x1 >= x2
  //  y1 <= y2 || y1 >= y2
  // For most cases this is a horrible data type, use a Rect instead :)
  struct Box
  {
    float mX1;
    float mY1;
    float mX2;
    float mY2;
  public:

    // @brief Create a empty box.
    Box();

    Box(const float x1, const float y1, const float x2, const float y2);

    float X1() const { return mX1; }
    float Y1() const { return mY1; }
    float X2() const { return mX2; }
    float Y2() const { return mY2; }
    
    float DeltaX() const { return mX2 - mX1; }
    float DeltaY() const { return mY2 - mY1; }

    float Width() const;
    float Height() const;
    float CenterX() const;
    float CenterY() const;
  };
}

#endif
