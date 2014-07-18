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

#include <dfmc/base/graphics/RawBitmapUtil.hpp>
#include <cassert>

namespace dfmc
{
  void RawBitmapUtil::Copy(RawBitmapEx& dstBitmap, const Point2& dstPos, const RawBitmap& srcBitmap, const Rectangle*const pSrcRect)
  {
    assert(dstBitmap.IsValid());
    assert(dstPos.X >= 0);
    assert(dstPos.Y >= 0);
    assert(srcBitmap.IsValid());

    const Rectangle srcRect = (pSrcRect != nullptr ? *pSrcRect : Rectangle(0, 0, srcBitmap.Width, srcBitmap.Height));
    assert(srcRect.X() >= 0);
    assert(srcRect.Y() >= 0);
    assert(srcRect.Width() >= 0 && srcRect.Width() <= srcBitmap.Width);
    assert(srcRect.Height() >= 0 && srcRect.Height() <= srcBitmap.Height);

    // Validate that the rect fit on the target bitmap
    assert((dstPos.X + srcRect.Width()) <= dstBitmap.Width);
    assert((dstPos.Y + srcRect.Height()) <= dstBitmap.Height);

    assert(dstBitmap.GetBytesPerPixel() == srcBitmap.GetBytesPerPixel());

    const int numBytesPerPixel = dstBitmap.GetBytesPerPixel();

    const int srcStride = srcBitmap.Stride;
    const uint8_t* pSrc = srcBitmap.pContent + (srcStride * srcRect.Y()) + (numBytesPerPixel*srcRect.X());
    const uint8_t*const pSrcEnd = pSrc + (srcStride * srcRect.Height());

    const int numBytes = srcRect.Width() * numBytesPerPixel;

    const int dstStride = dstBitmap.Stride;
    uint8_t* pDst = dstBitmap.pContent + (dstStride * dstPos.Y) + (numBytesPerPixel * dstPos.X);
    while( pSrc < pSrcEnd )
    {
      for( int x=0; x<numBytes; ++x )
      {
        pDst[x] = pSrc[x];
      }
      pSrc += srcStride;
      pDst += dstStride;
    }
  }


  void RawBitmapUtil::Swizzle(std::vector<uint8_t>& rDst, const RawBitmap& src, const int dstIdx0, const int dstIdx1, const int dstIdx2, const int dstIdx3)
  {
    assert(src.GetBytesPerPixel() == 4);

    rDst.resize(src.Width * src.Height * 4);
    Swizzle(&rDst[0], src, dstIdx0, dstIdx1, dstIdx2, dstIdx3);
  }


  void RawBitmapUtil::Swizzle(uint8_t* pDst, const RawBitmap& src, const int dstIdx0, const int dstIdx1, const int dstIdx2, const int dstIdx3)
  {
    assert( pDst != nullptr );
    assert( src.IsValid() );
    assert( dstIdx0 != dstIdx1 );
    assert( dstIdx0 != dstIdx2 );
    assert( dstIdx0 != dstIdx3 );
    assert( dstIdx1 != dstIdx2 );
    assert( dstIdx1 != dstIdx3 );
    assert( dstIdx2 != dstIdx3 );

    const uint8_t*const pSrc = src.pContent;
    const int srcWidth = src.Width;
    const int srcHeight = src.Height;
    const int srcStride = src.Stride;
    int offset = 0;
    for( int y=0; y<srcHeight; ++y )
    {
      for( int x=0; x<srcWidth; ++x )
      {
        const uint8_t b0 = pSrc[offset+(x * 4)+0];
        const uint8_t b1 = pSrc[offset+(x * 4)+1];
        const uint8_t b2 = pSrc[offset+(x * 4)+2];
        const uint8_t b3 = pSrc[offset+(x * 4)+3];
        pDst[offset+(x * 4)+dstIdx0] = b0;
        pDst[offset+(x * 4)+dstIdx1] = b1;
        pDst[offset+(x * 4)+dstIdx2] = b2;
        pDst[offset+(x * 4)+dstIdx3] = b3;
      }
      offset += srcStride;
    }
  }


}
