#ifndef DFMC_GRAPHICS_RENDER3D_TEXTUREAREA_HPP
#define DFMC_GRAPHICS_RENDER3D_TEXTUREAREA_HPP
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

namespace dfmc
{
  // @brief Describes a area on a texture of a given size
  //        The area is described in texture native format.
  struct TextureArea
  {
  private:
    float mX1;
    float mY1;
    float mX2;
    float mY2;
  public:
    TextureArea();
    TextureArea(const float x1, const float y1, const float x2, const float y2);

    float X1() const { return mX1; }
    float Y1() const { return mY1; }
    float X2() const { return mX2; }
    float Y2() const { return mY2; }

  };
}

#endif
