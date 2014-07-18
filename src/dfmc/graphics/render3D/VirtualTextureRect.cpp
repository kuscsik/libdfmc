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

#include <dfmc/graphics/render3D/VirtualTextureRect.hpp>
#include <cassert>

namespace dfmc
{
  VirtualTextureRect::VirtualTextureRect()
    : mTextureSize()
    , mSourceRectangle()
  {
  }

  VirtualTextureRect::VirtualTextureRect(const Point2& textureSize)
    : mTextureSize(textureSize)
    , mSourceRectangle(0, 0, textureSize.X, textureSize.Y)
  {
  }

  VirtualTextureRect::VirtualTextureRect(const Point2& textureSize, const Rectangle& sourceRectangle)
    : mTextureSize(textureSize)
    , mSourceRectangle(sourceRectangle)
  {
    assert( textureSize.X >= 0 );
    assert( textureSize.Y >= 0 );
    assert( sourceRectangle.IsValid() );
  }

  VirtualTextureRect::VirtualTextureRect(const TextureRect& textureRect)
    : mTextureSize(textureRect.GetTextureSize())
    , mSourceRectangle(textureRect.GetSourceRectangle())
  {
    assert( mTextureSize.X >= 0 );
    assert( mTextureSize.Y >= 0 );
    assert( mSourceRectangle.IsValid() );
  }

}
