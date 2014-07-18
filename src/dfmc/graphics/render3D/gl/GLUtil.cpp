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

#include "GLUtil.hpp"
#include <cassert>

namespace dfmc
{

  const TextureArea GLUtil::CalcTextureArea(const TextureRect& textureRect, const int timesX, const int timesY)
  {
    assert(timesX == 1 || (timesX != 1 && (textureRect.GetSourceRectangle().X() == 0 || textureRect.GetSourceRectangle().Width() == textureRect.GetTextureSize().X)));
    assert(timesY == 1 || (timesY != 1 && (textureRect.GetSourceRectangle().Y() == 0 || textureRect.GetSourceRectangle().Height() == textureRect.GetTextureSize().Y)));

    const Rectangle srcRect = textureRect.GetSourceRectangle();
    const Point2 sizeTex = textureRect.GetTextureSize();
    const float texW = float(sizeTex.X);
    const float texH = float(sizeTex.Y);

    assert(texW >= 0);
    assert(texH >= 0);

    const float x1 = (srcRect.Left() == 0 ? 0.0f : srcRect.Left() / texW);
    const float y1 = (srcRect.Top() == 0 ? 0.0f : srcRect.Top() / texH);
    const float x2 = (srcRect.Right() == sizeTex.X ? 1.0f * timesX : srcRect.Right() / texW);
    const float y2 = (srcRect.Bottom() == sizeTex.Y ? 1.0f * timesY : srcRect.Bottom() / texH);
    return TextureArea(x1, y1, x2, y2);
  }


  const TextureArea GLUtil::CalcTextureArea(const VirtualTextureRect& textureRect)
  {
    const Rectangle srcRect = textureRect.GetSourceRectangle();
    const Point2 sizeTex = textureRect.GetTextureSize();
    const float texW = float(sizeTex.X);
    const float texH = float(sizeTex.Y);

    assert(texW >= 0);
    assert(texH >= 0);

    const float x1 = (srcRect.Left() == 0 ? 0.0f : srcRect.Left() / texW);
    const float y1 = (srcRect.Top() == 0 ? 0.0f : srcRect.Top() / texH);
    const float x2 = (srcRect.Right() == sizeTex.X ? 1.0f : srcRect.Right() / texW);
    const float y2 = (srcRect.Bottom() == sizeTex.Y ? 1.0f : srcRect.Bottom() / texH);
    return TextureArea(x1, y1, x2, y2);
  }

}
