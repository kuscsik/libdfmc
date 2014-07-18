#ifndef DFMC_GRAPHICS_RENDER3D_VIRTUALTEXTURERECT_HPP
#define DFMC_GRAPHICS_RENDER3D_VIRTUALTEXTURERECT_HPP
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

#include "TextureRect.hpp"

namespace dfmc
{
  // @brief Describes a rectangle on a texture of a given size 
  //        The source rectangle can leave the texture area.
  struct VirtualTextureRect
  {
  private:
    Point2 mTextureSize;
    Rectangle mSourceRectangle;
  public:
    VirtualTextureRect();
    VirtualTextureRect(const Point2& textureSize);
    VirtualTextureRect(const Point2& textureSize, const Rectangle& sourceRectangle);
    VirtualTextureRect(const TextureRect& textureRect);

    const Rectangle GetSourceRectangle() const { return mSourceRectangle; }
    const Point2 GetTextureSize() const  { return mTextureSize; }
  };
}

#endif
