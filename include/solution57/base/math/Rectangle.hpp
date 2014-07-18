#ifndef DFMC_BASE_MATH_RECTANGLE_HPP
#define DFMC_BASE_MATH_RECTANGLE_HPP
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

#include <dfmc/base/math/Point2.hpp>

namespace dfmc
{
  struct Rectangle
  {
    int mX;
    int mY;
    int mWidth;
    int mHeight;
  public:

    Rectangle();
    Rectangle(const int x, const int y, const int width, const int height);
    Rectangle(const int left, const int right, const int top, const int bottom, const bool bReserved);

    bool IsValid() const { return mWidth >= 0 && mHeight >= 0; }

    int X() const { return mX; }
    int Y() const { return mY; }
    int Width() const { return mWidth; }
    int Height() const { return mHeight; }

    int Left() const { return mX; }
    int Top() const { return mY; }
    int Right() const { return mX + mWidth; }
    int Bottom() const  {return mY + mHeight; }

    int CenterX() const { return mX + (mWidth / 2); }
    int CenterY() const { return mY + (mHeight / 2); }

    const Point2 Center() const 
    { 
      return Point2(CenterX(), CenterY()); 
    }
  };

}

#endif
