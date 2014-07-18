#ifndef DFMC_BASE_GRAPHICS_RAWBITMAPEX_HPP
#define DFMC_BASE_GRAPHICS_RAWBITMAPEX_HPP
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

#include <dfmc/base/BasicTypes.hpp>

namespace dfmc
{
  struct RawBitmapEx
  {
    uint8_t* pContent;
    int Width;
    int Height;
    // The number of bytes that should be moved to get to the next scanline (can be negative)
    int Stride;

    RawBitmapEx();
    RawBitmapEx(uint8_t*const pContent, const int width, const int height);
    RawBitmapEx(uint8_t*const pContent, const int width, const int height, const int stride);

    int GetBytesPerPixel() const;

    bool IsValid() const;

  };

}

#endif
