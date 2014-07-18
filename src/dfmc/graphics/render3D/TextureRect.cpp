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

#include <dfmc/graphics/render3D/TextureRect.hpp>
#include <cassert>

namespace dfmc
{
  TextureRect::TextureRect()
    : mTextureSize()
    , mSourceRectangle()
  {
  }

  TextureRect::TextureRect(const Point2& textureSize)
    : mTextureSize(textureSize)
    , mSourceRectangle(0, 0, textureSize.X, textureSize.Y)
  {
  }

  TextureRect::TextureRect(const Point2& textureSize, const Rectangle& sourceRectangle)
    : mTextureSize(textureSize)
    , mSourceRectangle(sourceRectangle)
  {
    assert( textureSize.X >= 0 );
    assert( textureSize.Y >= 0 );
    assert( sourceRectangle.Left() >= 0 );
    assert( sourceRectangle.Top() >= 0 );
    assert( sourceRectangle.Right() <= textureSize.X );
    assert( sourceRectangle.Bottom() <= textureSize.Y );
  }
}
