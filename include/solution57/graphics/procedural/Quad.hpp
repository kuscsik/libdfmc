#ifndef DFMC_GRAPHICS_PROCEDURAL_QUAD_HPP
#define DFMC_GRAPHICS_PROCEDURAL_QUAD_HPP
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

#include <dfmc/base/math/Rect.hpp>
#include <dfmc/graphics/render3D/util/SimpleModel.hpp>
#include <dfmc/graphics/render3D/WindingOrder.hpp>
#include <dfmc/graphics/render3D/TextureArea.hpp>

namespace dfmc {
namespace procedural
{
  class Quad
  {
  public:
    static const SimpleModel Generate(const int verticesX, const int verticesY, const Rect& dstRect, const float zPos, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder);
    static const SimpleModel Generate(const int verticesX, const int verticesY, const int width, const int height, const Vector3& center, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder);

    static const SimpleModel GenerateStrip(const int verticesX, const int verticesY, const Rect& dstRect, const float zPos, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder);
    static const SimpleModel GenerateStrip(const int verticesX, const int verticesY, const int width, const int height, const Vector3& center, const TextureArea& textureArea, const bool bForwardNormal, const WindingOrder::Enum windingOrder);
  };
}}

#endif
