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

#include <dfmc/base/math/Rectangle.hpp>
#include <cassert>

namespace dfmc
{

  Rectangle::Rectangle() 
    : mX(0)
    , mY(0)
    , mWidth(0)
    , mHeight(0)
  {
  }

  Rectangle::Rectangle(const int x, const int y, const int width, const int height) 
    : mX(x)
    , mY(y)
    , mWidth(width)
    , mHeight(height)
  {
    assert(mWidth >= 0);
    assert(mHeight >= 0);
  }


  Rectangle::Rectangle(const int left, const int right, const int top, const int bottom, const bool)
    : mX(left)
    , mY(top)
    , mWidth(right - left)
    , mHeight(bottom - top)
  {
    assert(left <= right);
    assert(top <= bottom);
    assert(mWidth >= 0);
    assert(mHeight >= 0);
  }

}
