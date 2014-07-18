#ifndef DFMC_GRAPHICS_PROCEDURAL_VERTEXUTIL_HPP
#define DFMC_GRAPHICS_PROCEDURAL_VERTEXUTIL_HPP
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

#include <vector>
#include <dfmc/base/Noncopyable.hpp>
#include <dfmc/graphics/render3D/DataTypes.hpp>

namespace dfmc {
namespace procedural
{
  class VertexUtil : private Noncopyable
  {
  public:
    static int Append(std::vector<VertexPositionNormalTexture>& rDst, const int dstIndex, const std::vector<VertexPositionNormalTexture>& src);
    static int Append(std::vector<VertexPositionNormalTexture>& rDst, const int dstIndex, const std::vector<VertexPositionNormalTexture>& src, const Vector3& modVector);
  };

}}

#endif
