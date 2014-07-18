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

#include <dfmc/base/graphics/RawBitmapEx.hpp>
#include <cassert>

namespace dfmc
{
  RawBitmapEx::RawBitmapEx()
    : pContent(nullptr)
    , Width(0)
    , Height(0)
    , Stride(0)
  {
  }


  RawBitmapEx::RawBitmapEx(uint8_t*const pContent, const int width, const int height)
    : pContent(pContent)
    , Width(width)
    , Height(height)
    , Stride(width * 4)
  {
    assert( width >= 0 );
    assert( height >= 0 );
  }


  RawBitmapEx::RawBitmapEx(uint8_t*const pContent, const int width, const int height, const int stride)
    : pContent(pContent)
    , Width(width)
    , Height(height)
    , Stride(stride)
  {
    assert( width >= 0 );
    assert( height >= 0 );
  }


  int RawBitmapEx::GetBytesPerPixel() const
  {
    return 4;
  }


  bool RawBitmapEx::IsValid() const
  {
    return pContent != nullptr && Width >= 0 && Height >= 0;
  }
}
