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

#include <dfmc/graphics/render3D/TextureArea.hpp>
#include <cassert>

namespace dfmc
{

  TextureArea::TextureArea()
    : mX1(0.0f)
    , mY1(0.0f)
    , mX2(0.0f)
    , mY2(0.0f)
  {
  }


  TextureArea::TextureArea(const float x1, const float y1, const float x2, const float y2)
    : mX1(x1)
    , mY1(y1)
    , mX2(x2)
    , mY2(y2)
  {
  }
}
