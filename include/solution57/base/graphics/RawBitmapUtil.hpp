#ifndef DFMC_BASE_GRAPHICS_RAWBITMAPUTIL_HPP
#define DFMC_BASE_GRAPHICS_RAWBITMAPUTIL_HPP
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

#include <vector>
#include <dfmc/base/BasicTypes.hpp>
#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/base/math/Point2.hpp>
#include <dfmc/base/math/Rectangle.hpp>
#include <dfmc/base/graphics/RawBitmap.hpp>
#include <dfmc/base/graphics/RawBitmapEx.hpp>

namespace dfmc
{

  class RawBitmapUtil : private Noncopyable
  {
  public:
    // @brief Copy the src bitmap content to the dstBitmap at the desired location. 
    //        We assume that the src can fit on the dst at the given position. 
    //        We assume that both src and dst bitmaps are in the same pixel format.
    static void Copy(RawBitmapEx& dstBitmap, const Point2& dstPos, const RawBitmap& srcBitmap, const Rectangle*const pSrcRect = nullptr);

    // @brief Swizzle the color channels in a 32bpp image according to the supplied rules the rDst array will be resized to it can contain src image.
    static void Swizzle(std::vector<uint8_t>& rDst, const RawBitmap& src, const int dstIdx0, const int dstIdx1, const int dstIdx2, const int dstIdx3);

    // @brief Swizzle the color channels in a 32bpp image according to the supplied rules the pDst buffer must be able to contain the src image.
    static void Swizzle(uint8_t* pDst, const RawBitmap& src, const int dstIdx0, const int dstIdx1, const int dstIdx2, const int dstIdx3);
  };

}

#endif
