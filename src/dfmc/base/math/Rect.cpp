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

#include <dfmc/base/math/Rect.hpp>
#include <cassert>
#include <algorithm>

namespace dfmc
{

  Rect::Rect() 
    : mLeft(0.0f)
    , mTop(0.0f)
    , mRight(0.0f)
    , mBottom(0.0f)
    , mWidth(0.0f)
    , mHeight(0.0f)
  {
  }


  Rect::Rect(const float x, const float y, const float width, const float height) 
    : mLeft(x)
    , mTop(y)
    , mRight(x+width)
    , mBottom(y+height)
    , mWidth(width)
    , mHeight(height)
  {
    assert(mWidth >= 0.0f);
    assert(mHeight >= 0.0f);
  }


  Rect::Rect(const float left, const float top, const float right, const float bottom, const bool)
    : mLeft(left)
    , mTop(top)
    , mRight(right)
    , mBottom(bottom)
    , mWidth(std::max(right - left, 0.0f))
    , mHeight(std::max(bottom - top, 0.0f))
  {
    assert(left <= right);
    assert(top <= bottom);
    assert(mWidth >= 0.0f);
    assert(mHeight >= 0.0f);
  }
}
