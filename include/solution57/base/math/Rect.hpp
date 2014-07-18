#ifndef DFMC_BASE_MATH_RECT_HPP
#define DFMC_BASE_MATH_RECT_HPP
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
  struct Rect
  {
    // We store six values to keep the float rounding errors to a minimum :/
    // This means that the precision depends on how you create the Rect and how you modify it.
    float mLeft;
    float mTop;
    float mRight;
    float mBottom;
    float mWidth;
    float mHeight;
  public:

    // @brief Create a empty rect.
    Rect();

    //! @brief Create a rect based on location and dimensions (width >= 0 && height >= 0)
    Rect(const float x, const float y, const float width, const float height);

    //! @brief Create a object based on left, top, right and bottom coordinates
    //         left <= right && top <= bottom (the width is right-left and the height is bottom-top).
    //         Use this constructor when the precision of the right and bottom values is more important 
    //         than the width and height precision
    Rect(const float left, const float top, const float right, const float bottom, const bool bReserved);

    bool IsValid() const { return mWidth >= 0 && mHeight >= 0; }

    float X() const { return mLeft; }
    float Y() const { return mTop; }
    float Width() const { return mWidth; }
    float Height() const { return mHeight; }

    float Left() const { return mLeft; }
    float Top() const { return mTop; }
    float Right() const { return mRight; }
    float Bottom() const  {return mBottom; }

    float CenterX() const { return mLeft + (mWidth * 0.5f); }
    float CenterY() const { return mTop + (mHeight * 0.5f); }

    const Vector2 Center() const 
    { 
      return Vector2(CenterX(), CenterY()); 
    }
  };
}

#endif
