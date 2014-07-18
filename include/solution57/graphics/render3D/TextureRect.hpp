#ifndef DFMC_GRAPHICS_RENDER3D_TEXTURERECT_HPP
#define DFMC_GRAPHICS_RENDER3D_TEXTURERECT_HPP
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
#include <dfmc/base/math/Point2.hpp>

namespace dfmc
{
  // @brief Describes a rectangle on a texture of a given size
  struct TextureRect
  {
  private:
    Point2 mTextureSize;
    Rectangle mSourceRectangle;
  public:
    TextureRect();
    TextureRect(const Point2& textureSize);
    TextureRect(const Point2& textureSize, const Rectangle& sourceRectangle);

    const Rectangle GetSourceRectangle() const { return mSourceRectangle; }
    const Point2 GetTextureSize() const  { return mTextureSize; }
  };
}

#endif
