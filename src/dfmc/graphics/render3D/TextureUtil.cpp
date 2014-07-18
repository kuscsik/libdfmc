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

#include <dfmc/graphics/render3D/TextureUtil.hpp>
#include <dfmc/base/Exceptions.hpp>
#include "gl/GLUtil.hpp" 
#include <cassert>

namespace dfmc
{

  const TextureArea TextureUtil::CalcTextureArea(const TextureRect& textureRect)
  {
    return CalcTextureArea(textureRect, 1, 1);
  }

  const TextureArea TextureUtil::CalcTextureArea(const TextureRect& textureRect, const int timesX, const int timesY)
  {
    if (timesX != 1 && (textureRect.GetSourceRectangle().X() != 0 || textureRect.GetSourceRectangle().Width() != textureRect.GetTextureSize().X))
      throw UsageErrorException("Cant tile the texture in x unless the srcRect starts at zero and the source rect width is equal to the texture width");
    if (timesY != 1 && (textureRect.GetSourceRectangle().Y() != 0 || textureRect.GetSourceRectangle().Height() != textureRect.GetTextureSize().Y))
      throw UsageErrorException("Cant tile the texture in y unless the srcRect starts at zero and the source rect width is equal to the texture width");
    return GLUtil::CalcTextureArea(textureRect, timesX, timesY);
  }

  const TextureArea TextureUtil::CalcTextureArea(const VirtualTextureRect& textureRect)
  {
    return GLUtil::CalcTextureArea(textureRect);
  }

}
